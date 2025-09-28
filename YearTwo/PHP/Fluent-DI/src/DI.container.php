<?php

session_start();

use FluetnDI\Attributes\Singleton;
use FluetnDI\Attributes\Scoped;
use FluetnDI\Attributes\Transient;

require_once("./global/global-constants.php");

#[Singleton]
class A{
    public int $counter = 0;

    public function __construct(D $D)
    {
        
    }
}

#[Scoped]
class B{
    public int $counter = 0;

    public function __construct(A $A)
    {
        
    }
}

#[Singleton]
class C{
    public function __construct(A $A)
    {
        
    }
}

#[Singleton]
class D{
    public function __construct()
    {
            
    }
}

#[Singleton]
class E{
    public function __construct(C $C, A $A)
    {
        
    }
}

#[Transient]
class F{
    public int $counter = 0;

    public function __construct(G $G)
    {
        
    }
}


#[Transient]
class G{
    public function __construct(C $C, B $B)
    {
        
    }
}

/**
 * Dependency Injection Container with lifecycle management
 * 
 * Automatically resolves class dependencies with singleton, scoped and transient lifecycles.
 * Performs dependency graph validation and cyclic dependency detection.
 */
class DIContainer
{
    /**
     * Registered dependencies categorized by lifecycle type
     * @var array<string, array<class-string>>
     */
    public array $dependencies;

    /**
     * Instances of resolved dependencies
     * @var array<class-string, object>
     */
    public array $instances;

    /**
     * Lifecycle type mapping for each class
     * @var array<class-string, string>
     */
    private array $lifecycleMap = [];

    /**
     * Dependency resolution order
     * @var array<class-string>
     */
    private array $resolutionOrder = [];

    /** @var self|null Singleton container instance */
    private static ?DIContainer $containerInstance = null;

    /**
     * Get singleton instance of the container
     * 
     * @return self
     */
    public static function getInstance(): DIContainer {
        if (self::$containerInstance === null) {
            self::$containerInstance = new DIContainer();
        }

        return self::$containerInstance;
    }

    private function __construct() 
    {
        $this->dependencies = [
            __SINGLETON__ => [],
            __SCOPED__ => [],
            __TRANSIENT__ => []
        ];

        if (!isset($_SESSION['instances'])) {
            $_SESSION['instances'] = [];
        }
        
        $this->instances = &$_SESSION['instances'];

        print_r($_SESSION['instances']);

        $this->Scan();
        $matrixData = $this->BuildDependencyMatrix();
        $this->resolutionOrder = $this->sortDependencies($matrixData['matrix'], $matrixData['classes']);
    }

    /**
     * Execute code within a scoped context
     * 
     * @param callable $context Callback function receiving the container instance
     * @throws RuntimeException
     */
    public function usingContext(callable $context)
    {
        try {
            $context($this);
        } finally {
            $this->clearScopedInstances();
        }
    }

    private function clearScopedInstances()
    {
        foreach ($this->instances as $className => $instance) {
            if ($this->lifecycleMap[$className] === __SCOPED__) {
                unset($this->instances[$className]);
            }
        }
    }

    /**
     * Get dependency instance by class name
     * 
     * @template T
     * @param class-string<T> $className
     * @return T
     * @throws RuntimeException
     */
    public function getDependency(string $className): object {
        $instance = $this->instances[$className] ?? null;

        if($instance === null){
            $instance = $this->buildInstance($className);

            if ($this->lifecycleMap[$className] === __SINGLETON__ || $this->lifecycleMap[$className] === __SCOPED__ ){
                $this->instances[$className] = $instance;
            }
        }
        
        return $instance;
    }

    /**
     * Build class instance with dependency resolution
     * 
     * @template T
     * @param class-string<T> $className
     * @return T
     * @throws ReflectionException|RuntimeException
     */
    public function buildInstance(string $className): object {
        $reflectionClass = new ReflectionClass($className);
        $constructor = $reflectionClass->getConstructor();
    
        if (is_null($constructor)) {
            return new $className();
        }
    
        $parameters = $constructor->getParameters();
        $dependencies = [];
    
        foreach ($parameters as $param) {
            $type = $param->getType();
    
            if ($type === null || $type->isBuiltin()) {
                throw new RuntimeException("Cannot resolve parameter '{$param->getName()}' in {$className}");
            }
    
            $dependencyClassName = $type->getName();
            $dependencies[] = $this->getDependency($dependencyClassName); 
        }
    
        return $reflectionClass->newInstanceArgs($dependencies);
    }

    
    /**
     * Scan and register classes with lifecycle attributes
     * 
     * @throws ReflectionException
     */
    public function Scan()
    {
        $declaredClasses = get_declared_classes();  

        // [FIND ALL TRANSIENT CLASSES]
        $this->dependencies[__TRANSIENT__] = $this->FindByAttribute($declaredClasses, __TRANSIENT__);

        // [FIND ALL SCOPED CLASSES]
        $this->dependencies[__SCOPED__] = $this->FindByAttribute($declaredClasses, __SCOPED__);

        // [FIND ALL SINGLETON CLASSES]
        $this->dependencies[__SINGLETON__] = $this->FindByAttribute($declaredClasses, __SINGLETON__);

        foreach ([__SINGLETON__, __SCOPED__, __TRANSIENT__] as $type) {
            foreach ($this->dependencies[$type] as $class) {
                $this->lifecycleMap[$class] = $type;
            }
        }
    }

    public function findByAttribute($declaredClasses, $attribute)
    {
        $classes = [];
        
        foreach ($declaredClasses as $class) {
            $reflectionClass = new ReflectionClass($class);
            
            $attributes = $reflectionClass->getAttributes($attribute);
            
            if (!empty($attributes)) {
                array_push($classes, $class);
            }
        }

        return $classes;
    }

    private function isValidLifecycle($parentLifecycle, $childLifecycle)
    {
        $hierarchy = [
            __TRANSIENT__ => 0,
            __SCOPED__ => 1,
            __SINGLETON__ => 2
        ];

        return $hierarchy[$childLifecycle] >= $hierarchy[$parentLifecycle];
    }

    /**
     * Build graph matrix
     * 
     * @throws RuntimeException
     */
    public function buildDependencyMatrix()
    {
        $allClasses = array_merge(
            $this->dependencies[__SINGLETON__],
            $this->dependencies[__SCOPED__],
            $this->dependencies[__TRANSIENT__]
        );
        
        $classCount = count($allClasses);
        $matrix = array_fill(0, $classCount, array_fill(0, $classCount, 0));
        $classIndexes = array_flip($allClasses);

        foreach ($allClasses as $class) {
            $reflectionClass = new ReflectionClass($class);
            $constructor = $reflectionClass->getConstructor();

            if (!$constructor) continue;

            $classLifecycle = $this->lifecycleMap[$class];  

            foreach ($constructor->getParameters() as $param) {
                $paramType = $param->getType();
                
                if ($paramType && !$paramType->isBuiltin()) {
                    $dependencyClass = $paramType->getName();

                    // Check if dependency is registered
                    if (!isset($classIndexes[$dependencyClass])) {
                        throw new RuntimeException("Unregistered dependency: {$dependencyClass}");
                    }

                    // Validate lifecycle hierarchy
                    $dependencyLifecycle = $this->lifecycleMap[$dependencyClass];
                    if (!$this->isValidLifecycle($classLifecycle, $dependencyLifecycle)) {
                        throw new RuntimeException("Invalid lifecycle: {$class} ({$classLifecycle}) depends on {$dependencyClass} ({$dependencyLifecycle})");
                    }

                    // Build dependency matrix
                    $i = $classIndexes[$class];
                    $j = $classIndexes[$dependencyClass];
                    $matrix[$i][$j] = 1;
                }
            }
        }

        return ['matrix' => $matrix, 'classes' => $allClasses];
    }

    public function sortDependencies(array $matrix, array $classes)
    {
        $queue = [];
        $originalSize = count($matrix);
        $indexMap = array_keys($matrix);

        while (count($queue) < $originalSize) {
            $found = false;

            foreach ($matrix as $i => $row) {
                if (!in_array(1, $row, true)) {
                    $originalIndex = $indexMap[$i];
                    array_push($queue, $classes[$originalIndex]);

                    unset($matrix[$i]);

                    foreach ($matrix as &$otherRow) {
                        unset($otherRow[$originalIndex]);
                    }

                    $matrix = array_values($matrix);
                    unset($indexMap[$i]);
                    $indexMap = array_values($indexMap);
                    $found = true;
                    break;
                }
            }

            if (!$found) {
                throw new RuntimeException("Cyclic dependency detected!");
            }
        }

        return $queue;
    }
}
# Запуск

1.  Скачать проект с github репозитория.
2.  Установить XAMPP и скопировать проект в директорию htdocs 
3.  Запустить XAMPP и запустить веб сервер
4.  Стучаться на сервер по http://localhost/Fluent-DI/src/test.php

# Описание работы

## Цель работы - создать простой механизм внедрения зависимостей с различными циклами жизни

## Содержание проекта:

Класс DIContainer представляет собой объект для внедрения зависимостей.

```php

class DIContainer
{
    public array $dependencies;
    public array $instances;

    private array $lifecycleMap = [];
    private array $resolutionOrder = [];

    private static ?DIContainer $containerInstance = null;

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

    public function usingContext(callable $context)
    {
        ...
    }

    private function clearScopedInstances()
    {
        ...
    }

    public function getDependency(string $className): object {
        ...
    }

    public function buildInstance(string $className): object {
        ...
    }

    public function Scan()
    {
        ...
    }

    public function findByAttribute($declaredClasses, $attribute)
    {
        ...
    }

    private function isValidLifecycle($parentLifecycle, $childLifecycle)
    {
        ...
    }

    public function buildDependencyMatrix()
    {
        ...
    }

    public function sortDependencies(array $matrix, array $classes)
    {
       ...
    }
}
```


Он реализует паттерн Singleton и должен быть один на проект.

Метод Scan занимается поиском зависимостей

```php
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

```

Метод getDependency возвращает инстанс зависимости

```php
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
```

Метод buildInstance занимается созданием инстансов зависимостей

```php
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
```

Метод usingContext подразумевает использование scoped зависимостей в контексте (Как правило это будет один http запрос, но метод позволит сделать и другие скоупы)

```php
    public function usingContext(callable $context)
    {
        try {
            $context($this);
        } finally {
            $this->clearScopedInstances();
        }
    }
```

Специфика php подразумевает, что все созданыне объекты сами по себе scoped и при возврате ответа на фронтенд, зависимости удаляются. Для того чтобы реализовать singleton необходим сторонний инструмент для кеширования зависимости между запросами. В данном примере всё хранится в сессии, но сессия уникальна для конкретного юзера. Таким образом этот синглтон будет уникален для пользователя. Чтобы сделать глобальный синглтон необходимо подключить сторонние сервисы для кеширования, например redis.

Алгоритм построения зависимостей подразумевает их сортировку. Я представил зависимости как связные графы и строю матрицу инцидентности для них. Построив матрицу я ищу строку состоящую из 0. Если таковой нет, значит в коде есть циклическая зависимость. Если такая есть, то я удаляю её и соответствующий ей столбец.

```php
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
```

Далее я сортирую зависисмости и организую их в очередь. 

```php
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
```

Сканирование зависимостей идёт по атрибутам.

Тестовые зависимости:

```php
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
```

Результат работы программы ```Array ( [D] => D Object ( ) [A] => A Object ( [counter] => 46 ) [C] => C Object ( ) [B] => B Object ( [counter] => 0 ) ) Array ( [0] => D [1] => A [2] => C [3] => E [4] => B [5] => G [6] => F ) 47 48 1 2 1 1```

Вывод не очень презентабельный, но он показывает, что DI работает. Первые два числа это вызовы к singleton счётчику, вторые это scoped и третьи это transient. 

Выведенный на экран массив представляет собой очередь т.е порядок для построения зависимостей.
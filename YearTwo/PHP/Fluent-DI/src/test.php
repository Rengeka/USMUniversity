<?php

require_once("./DI.container.php");

$container = DIContainer::GetInstance();
$container->Scan();
$matrixData = $container->BuildDependencyMatrix();
$resolutionOrder = $container->SortDependencies($matrixData['matrix'], $matrixData['classes']);

print_r($resolutionOrder);


// Test singleton
$singleton = $container->getDependency(A::class);

$singleton->counter++;
echo $singleton->counter;

$singleton->counter++;
echo $singleton->counter;

// Test scoped

$container->usingContext(function($context) {
    $scoped = $context->getDependency(B::class);

    $scoped->counter++;
    echo $scoped->counter;

    $scoped = $context->getDependency(B::class);

    $scoped->counter++;
    echo $scoped->counter;
});

/*
try {
    $scoped->counter++;
    echo $scoped->counter;
} catch(Throwable $ex){
    echo "Exception: " . $ex->getMessage();
}*/

// Test transient
$transient = $container->getDependency(F::class);
$transient->counter++;
echo $transient->counter;

$transient = $container->getDependency(F::class);
$transient->counter++;
echo $transient->counter;
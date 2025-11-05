<?php

use PHPUnit\Framework\TestCase;
use App\Calculator;

class CalculatorTest extends TestCase
{
    public function testAdd()
    {
        $calc = new Calculator();
        $this->assertEquals(4, $calc->add(2, 2));
    }

    public function testSubtract()
    {
        $calc = new Calculator();
        $this->assertEquals(0, $calc->subtract(2, 2));
    }
}
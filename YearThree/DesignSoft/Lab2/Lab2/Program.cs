using Lab2;
using Lab2.Steps;

var pipeline = new Pipeline<Context>();
var pipeline2 = new Pipeline<TestContext>();

var context = new Context();

pipeline.AddStep(new TestStep());
pipeline.AddStep(new AnotherTestStep());
pipeline.AddStep(SingletonStep.Instance);

var corStep = new ChainOfResponsibilityStep(new ChainOfResponsibilityStep(new ChainOfResponsibilityStep()));
pipeline.AddStep(corStep);
pipeline.AddStep(new DecoratorStep(new TestStep()));

pipeline.Execute(context);
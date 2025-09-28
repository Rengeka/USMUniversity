#include <iostream>

class StackElement 
{
private:

    int _value;
    StackElement* _nextElement;

public:

    StackElement(int value) 
    {
        _value = value;
        _nextElement == NULL;
    }

    int GetValue() 
    {
        return _value;
    }

    StackElement* GetNextElement() 
    {
        return _nextElement;
    }

    void SetNextElement(StackElement* el) 
    {
        _nextElement = el;
    }
};

class Stack {
private:
    StackElement* _firstElement;

public:

    Stack(StackElement* firstElement)
    {
        _firstElement = firstElement;
    }

    void CreateElement(int value) 
    {
        StackElement* el = _firstElement;
        while (el->GetNextElement() != NULL)
        {
            el = el->GetNextElement();
        }

        el->SetNextElement(new StackElement(value));
    }

    void AddElement(StackElement* el)
    {

    }

    void AddElement(int value, int number) 
    {

    }

    void DeleteElement(int number) 
    {

    }

    int GetElementValue(int number) 
    {
        return 0;
    }

    void PrintStack() 
    {
        StackElement* el = _firstElement;
        do {
            std::cout << " " << el->GetValue();
        } while (el->GetNextElement() != NULL);
        free(el);
    }
};

int main()
{
    Stack* stack = new Stack(new StackElement(1));
    stack->PrintStack();

    stack->CreateElement(2);
    stack->CreateElement(3);
    stack->CreateElement(4);
    stack->PrintStack();
}

package main

import "fmt"

type State int

const (
    S0 State = iota
    S1
    S2
    S3
    ERROR
)

type Automaton struct {
    State State
}

func main() {
    correctWords := []string{
        "aaabddd",
        "bd",
        "abd",
    }

    wrongWords := []string{
        "aabad",
        "d",
        "aab",
        "bddda",
        "labd",
    }

    automaton := Automaton{State: S0}

    for _, word := range correctWords {
        result := IdentifyWord(&automaton, word)
        fmt.Println("Word:", word, "Result:", result)
        automaton.State = S0
    }

    for _, word := range wrongWords {
        result := IdentifyWord(&automaton, word)
        fmt.Println("Word:", word, "Result:", result)
        automaton.State = S0
    }
}

func IdentifyWord(automaton *Automaton, word string) bool {
    for _, char := range word {
        automaton.ProcessChar(char)
        if automaton.State == ERROR {
            return false
        }
    }
	
    return automaton.State == S3
}

func (automaton *Automaton) ProcessChar(c rune) {
    switch automaton.State {
    case S0:
        if c == 'a' {
            automaton.State = S1
        } else if c == 'b' {
            automaton.State = S2
        } else {
            automaton.State = ERROR
        }
    case S1:
        if c == 'b' {
            automaton.State = S2
        } else if c == 'a' {
           automaton.State = S2
		} else {
            automaton.State = ERROR
        }
    case S2:
        if c == 'd' {
            automaton.State = S3
        } else {
            automaton.State = ERROR
        }
    case S3:
        if c == 'd' {
           automaton.State = S3 
		} else {
            automaton.State = ERROR
        }
    }
}
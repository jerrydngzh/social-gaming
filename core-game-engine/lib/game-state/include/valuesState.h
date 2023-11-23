//These can be constant, players, audience, or variable values
#pragma once

class Value {
 //Should have a name if its not mapped to a name
 //Should have a type / kind
 //Should have a way to know if its a constant, player, audience, or variable value (belongsTo?)
    
 //Values may themselves be 
 //(1) maps from names to values *should have a getKeys() method
 //(2) lists of values
 //(3) literal strings, numbers, or booleans.
};

//stores list of current values and getValue(string nameOfValue)
class ValuesState {
 //Maybe should have a map of variable name to value?
};
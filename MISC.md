# Colony Programming Language

## Goals

* High-level programming language.
* Static typing.
* Multi-paradigm programming language.
* Mostly functional language with practical parts from imperative languages.
* Garbage collected: Reference counting, reference cycles almost impossible due to immutability.
* Immutable (persistent) data by default.
* Mutable (transient) data only when nobody can observe it, such as for temporary variables.
* Syntax inspired by C, Rust, Go.
* Everything is an expression.


## 1. Imperative programming
    
Imperative programming is a programming paradigm that uses statements that change a program's state.

https://en.wikipedia.org/wiki/Imperative_programming


## 2. Functional programming

In computer science, functional programming is a programming paradigm — a style of building the structure and elements of computer programs — that treats computation as the evaluation of mathematical functions and avoids changing-state and mutable data.

It is a declarative programming paradigm in that programming is done with expressions or declarations instead of statements.

https://en.wikipedia.org/wiki/Functional_programming


### 2.1. First-class function

A programming language is said to have first-class functions if it treats functions as first-class citizens.

This means the language supports passing functions as arguments to other functions, returning them as the values from other functions, and assigning them to variables or storing them in data structures.

https://en.wikipedia.org/wiki/First-class_function


### 2.2 Higher-order function

A higher-order function is a function that does at least one of the following:

* takes one or more functions as arguments (i.e. procedural parameters),
* returns a function as its result.

https://en.wikipedia.org/wiki/Higher-order_function


## 3. Purely functional programming
    
Purely functional programming usually designates a programming paradigm - a style of building the structure and elements of computer programs - that treats all computation as the evaluation of mathematical functions. 

Purely functional programming may also be defined by forbidding changing-state and mutable data.

Purely functional programming consists in ensuring that functions, inside the functional paradigm, will only depend on their arguments, regardless of any global or local state.

https://en.wikipedia.org/wiki/Purely_functional_programming


## 4. Mutability

Changeable object whose state *can* be modified after it is created.

```
a = []
a.append(10)
a.append(20)

a == [10, 20]
```


## 5. Immutability

Unchangeable object whose state *cannot* be modified after it is created. 

```
a = ()
a0 = a + (10,)
a1 = a0 + (20,)

a == ()
a0 == (10,)
a1 == (10, 20)

a0_0 = a0. + (111,)
a0 == (10,)
a0_0 == (10, 111)
```


## 6. Persistent data structure
    
A persistent data structure is a data structure that always preserves the previous version of itself when it is modified. Such data structures are effectively immutable, as their operations do not (visibly) update the structure in-place, but instead always yield a new updated structure.

*Partially persistent*: A data structure is partially persistent if all versions can be accessed but only the newest version can be modified.

*Fully persistent*: The data structure is fully persistent if every version can be both accessed and modified.

*Confluently persistent*: If there is also a meld or merge operation that can create a new version from two previous versions, the data structure is called confluently persistent. 

*Ephemeral*: Structures that are not persistent are called ephemeral.

https://en.wikipedia.org/wiki/Persistent_data_structure#Copy_on_Write


### 6.1 Copy-on-write

One method for creating a persistent data structure is to use a platform provided ephemeral data structure such as an array to store the data in the data structure and copy the entirety of that data structure using copy on write semantics for any updates to the data structure.

```
a0 = [0, 0, 0, 0, 0]
a1 = [*a0[0:2], 1, *a0[3:5]]
a0 == [0, 0, 0, 0, 0]
a1 == [0, 0, 1, 0, 0]
```

https://en.wikipedia.org/wiki/Persistent_data_structure#Copy_on_Write


### 6.2 Linked lists

Once a node in the list has been allocated, it cannot be modified, only copied, referenced or deallocated.

```
# 'A' -> 'B' -> 'C'
('A', ('B', ('C', None)))
```


### 6.3 Persistent hash array mapped trie

A specialized variant of a hash array mapped trie that will preserve previous versions of itself on any updates. It is often used to implement a general purpose persistent map data structure.

https://en.wikipedia.org/wiki/Persistent_data_structure#Persistent_hash_array_mapped_trie


## 7. Retroactive data structure

A retroactive data structure is a data structure which supports efficient modifications to a sequence of operations that have been performed on the structure. These modifications can take the form of retroactive insertion, deletion or updating an operation that was performed at some time in the past

https://en.wikipedia.org/wiki/Retroactive_data_structure


## 8. Transient Data Structures

Fast "locally mutable" data structures.

Transient data structures are always created from an existing persistent data structure.

It shares structure with its source, just as persistent copies share structure.

Creating one does not modify the source, and the source cannot be modified via use of the transient. Your source data is immutable and persistent as always.

Each result of a transient operation shares (mutable) structure with the previous.

When you are finished building up your results, you can create a persistent data structure by calling persistent! on the transient. This operation is also O(1).

https://clojure.org/reference/transients


## 9. Algebraic data types

An algebraic data type is a kind of composite type.

A type formed by combining other types.

https://en.wikipedia.org/wiki/Algebraic_data_type


### 9.1 Product types

A product of types is another, compounded, type in a structure. The "operands" of the product are types, and the structure of a product type is determined by the fixed order of the operands in the product.

Tuples and records.

A tuple is a finite ordered list (sequence) of elements.

```
let tup: (i32, f64, u8) = (500, 6.4, 1);
```

A record (also called a structure, struct, or compound data) is a basic data structure.

```
struct date {
   int year;
   int month;
   int day;
};
```

https://en.wikipedia.org/wiki/Product_type
https://en.wikipedia.org/wiki/Tuple
https://en.wikipedia.org/wiki/Record_(computer_science)
https://doc.rust-lang.org/nightly/book/ch03-02-data-types.html#the-tuple-type


### 9.2 Sum types

Is a data structure used to hold a value that could take on several different, but fixed, types.

Also called tagged or disjoint unions, coproduct.

Example in Python without ADT:
```
# 'A' -> 'B' -> 'C'
('A', ('B', ('C', None)))
```

Here is an example of how a singly linked list would be declared in Haskell with ADT:

```
data List a = Nil | Cons a (List a)
```

In C, a union is a value that may have any of several representations or formats within the same position in memory.

```
union bar { int a; float b; }
```

https://en.wikipedia.org/wiki/Tagged_union
https://en.wikipedia.org/wiki/Union_type


## 10. Functional programming concepts

* First-class function: functions as values.
* High-order functions: functions taking other functions as arguments and/or returning functions.
* Partial application: currying.
* Semigroup: Semigroup must have a concat method.
* Monoids: both inner data will have the same type, and when we return result, it will have also the same type and this types will be equal.
* Foldable: A value which has a Foldable must provide a reduce method.
* Functors: you apply a function to a wrapped value using fmap or `<$>` .
* Applicative Functors: you apply a wrapped function to a wrapped value using `<*>` .
* Monads: you apply a function that returns a wrapped value, to a wrapped value using `>>=` .

https://soundcloud.com/lambda-cast
https://sanderv1992.github.io/fp/
https://en.wikipedia.org/wiki/Currying

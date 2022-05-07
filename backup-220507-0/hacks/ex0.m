//
// primitive values
//
a: i64 = 1_i64
a := 1_i64
a = 1 // i64

a: i32 = 10_i32
a = 20_i32

b: f32 = 1.0_f32
b = 2.0_f32

c := 1.0_f64
c: f64 = 1.0_f64
c = 2.0 // f64

//
// tuple
//
v: tuple = tuple(1, 2)                                  // tuple<object, object>
v: tuple = tuple<i64, i64>(1, 2)                        // tuple<i64, i64>
v: tuple<i64, i64> = tuple<i64, i64>(1, 2)              // tuple<i64, i64>
v: tuple<i64, i64> = (1, 2)                             // tuple<i64, i64>
v := tuple(1, 2)                                        // tuple<object, object>
v := tuple<i64, i64>(1, 2)                              // tuple<i64, i64>
v := ()                                                 // tuple<>
v := (1, 2)                                             // tuple<object, object>
v := (v[0] * 2.0, v[1] * 2.0)                           // tuple<object, object>

//
// list
//
c: list = list()                                        // list<object>
c: list = list<i64>()                                   // list<i64>
c: list<i64> = list<i64>()                              // list<i64>
c: list<i64> = []                                       // list<i64>
c := list()                                             // list<object>
c := list<i64>()                                        // list<i64>
c := []                                                 // list<object>
c := [-1]                                               // list<object>

c = c.push(0)
c = c.push(10)
c = c.push(20)

v: i32 = c[0] + c[1] + c[2]

//
// dict
//
d: dict<str, i64> = dict<str, i64>()                    // dict<str, i64>
d: dict<str, i64> = {}                                  // dict<str, i64>
d := dict<str, i64>()                                   // dict<str, i64>
d := {}                                                 // dict<object, object>
d := {'x': 0, 'y': 0}                                   // dict<object, object>
d := {.x: 0, .y: 0}                                     // dict<object, object>

d['x'] = 0
d['y'] = 1

d.x = 0
d.y = 1

//
// function
//
f0: fn = (x: i64, y: i64) -> i64 { x + y }
f0 := (x: i64, y: i64) -> i64 { x + y }
f0 := (x, y) -> i64 { x + y }
f0 := (x, y) -> { x + y }

F1: type = fn<R: type=i64 | f64, T: type=i64 | f64, S: type=i64 | f64>
F1: type = fn<R: type, T: type, S: type>
F1: type = fn<R, T, S>

f1: fn = F1((x: R, y: T) -> S { x + y })
r1: i64 = f1<i64, i64, i64>(1, 2)

f1a: fn = f1<i64, i64, i64>
r1a: i64 = f1a(1, 2)

//
// object
//
A := {
    .__name__: 'A',
    .__type__: type,
    .__new__: (self, x: i64) -> A {
        self += {
            .__type__: A,
            .x = x,
        }
    },
    .__add__: (self, other: A) -> A {
        res = A(self.x + other.x)
    }
}

a0 := A(10)
a1 := A(20)
a2 := a0 + a1

//
// object
//
A := type({
    .__name__: 'A',
    .__new__: (self, x: i64) -> A {
        // self = {...self, .x: x}
        self += {.x: x}
    },
    .__add__: (self, other: A) -> A {
        res = A(self.x + other.x)
    }
})

a0 := A(10)
a1 := A(20)
a2 := a0 + a1

//
// object 
//
A := type({
    .__name__: 'A',
    .__new__: (self, x: i64) -> A {
        // self = {...self, .x: x}
        self += {.x: x}
    },
    .__add__: (self, other: A) -> A {
        res = A(self.x + other.x)
    }
})

B := type({
    .__name__: 'B',
    .__new__: (self, y: i64) -> B {
        // self = {...self, .y: y}
        self += {.y: y}
    },
    .__add__: (self, other: B) -> B {
        res = B(self.y + other.y)
    }
})

C := type({
    .__name__: 'C',
    .__bases__: [A, B],
    .__new__: (self, x: i64, y: i64) -> B {
        // self = {...self, .x: x, .y: y}
        self += {.x: x, .y: y}
    },
    .__add__: (self, other: C) -> C {
        res = C(self.x + other.x, self.y + other.y)
    }
})

c0 := C(1, 2)
c1 := C(2, 3)
c2 := c0 + c1

//
// union
//
T: type = i32 | f32

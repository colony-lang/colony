//
// struct type
//
P: struct = (x: f64=0.0, y: f64=0.0)        // struct
P: type = (x: f64=0.0, y: f64=0.0)          // struct is subtype of type
P: object = (x: f64=0.0, y: f64=0.0)        // struct is subtype of type
p: P = P(1.0, 2.0)                          // P
p: P = P(x=1.0, y=2.0)                      // P
x := p.x
y := p.y

//
// list
//
p: list = [1.0, 2.0, 3.0, 4.0]              // list
p: list<f64> = [1.0, 2.0, 3.0, 4.0]         // list<f64>
p: object = [1.0, 2.0, 3.0, 4.0]            // list is subtupe of object
x := p[0]
y := p[1]

//
// dict
//
p: dict = {1: 2.0, 3: 4.0}                  // dict
p: dict<i64, f64> = {1: 2.0, 3: 4.0}        // dict<i64, f64>
p: object = {1: 2.0, 3: 4.0}                // dict is subtupe of object
x := p[1]
y := p[3]

//
// generic struct
//
G: generic_struct = <X:=type, Y:=type, R:=type>     // generic_struct
G: type = <X:=type, Y:=type, R:=type>               // generic_struct is subtype of type
G: object = <X:=type, Y:=type, R:=type>             // generic_struct is subtype of type
g: G = G<i64, i64, f64>                             // G
g: G = G<X=i64, Y=i64, R=f64>                       // G
X := G.X
Y := G.Y

//
// parameterized struct type
//
P: param_struct = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default)
P: type = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default)
P: object = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default)
p0: P = P<i64>(1, 2)
p1: P = P<i64>(2, 3)

//
// parameterized function type
//
F: param_fn = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default) -> T
F: type = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default) -> T
F: object = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default) -> T

f: F = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default) -> T -> { x + y }
f: F = F -> { x + y }
f: fn = F -> { x + y }
f: object = F -> { x + y }

r0: i64 = f<i64>(1, 2)
r1: i64 = f<i64>(2, 3)

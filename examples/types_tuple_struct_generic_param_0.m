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
p: object = [1.0, 2.0, 3.0, 4.0]            // tuple is subtupe of object
x := p[0]
y := p[1]

//
// dict
//
p: dict = {1: 2.0, 3: 4.0}                  // list
p: object = {1: 2.0, 3: 4.0}                // tuple is subtupe of object
x := p[1]
y := p[3]

//
// generic struct
//
G: generic_struct = <X:=type, Y:=type, R:=type>     // generic_type, has :=
G: type = <X:=type, Y:=type, R:=type>               // generic_type is subtype of type, has :=
G: object = <X:=type, Y:=type, R:=type>             // generic_type is subtype of type, has :=
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

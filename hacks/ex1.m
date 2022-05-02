//
// primitive values
//
a: i64 = 1_i64
a := 1_i64
a = 1                                                                           // i64

a: i32 = 10_i32
a = 20_i32

b: f32 = 1.0_f32
b = 2.0_f32

c := 1.0_f64
c: f64 = 1.0_f64
c = 2.0                                                                         // f64

//
// tuple
//
v := (1, 2)

T: type = tuple<x: type=i64, y: type=i64>
t: T = T(1, 2)
t: T = (1, 2)
t := T(1, 2)

//
// list
//
l := [1, 2]

L: type = list<t: type=i64>
l: L = L([1, 2])
l: L = [1, 2]
l := L([1, 2])

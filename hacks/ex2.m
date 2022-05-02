//
// primitive
//
a: i64 = 1              // i64
a: i64 = 1_i64          // i64
a := 1                  // i64
a := 1_i64              // i64

a: f64 = 1.0            // f64
a: f64 = 1.0_f64        // f64
a := 1.0                // f64
a := 1.0_f64            // f64

a: u8 = 255_u8          // u8
a := 255_u8             // u8

a: bytes = b'abc'       // bytes
a := b'abc'             // bytes

a: str = 'abc'          // str
a := 'abc'              // str

//
// tuple
//
P := (x: f64=0.0, y: f64=0.0)
p0: P = P(1.0, 2.0)
p1: P = P(2.0,)
p2: P = P(p0.x + p1.x, p0.y + p1.y)
p2 := P(p0.x + p1.x, p0.y + p1.y)

P := (x: f64, y: f64, z: f64)
p0 := P(1.0, 2.0, 3.0)
p1 := P(1.0, 2.0, 3.0)
p2 := P(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z)

//
// function
//
f := (x: f64, y: f64) -> f64 -> {
    r: f64 = x + y
    r
}

a := f(1.0, 2.0)

//
// object/type
//
P := (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := (
        // __type__ := tuple,
        __base__ := [object],
        __name__ := 'P',
        __add__ := (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

P := (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type('P', [object],
        __add__ := (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

P := (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(
        __add__ := (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

p0 := P(1.0, 2.0, 3.0)
p1 := P(1.0, 2.0, 3.0)
// p2 := p0.__type__.__add__(p0, p1)
p2 := p0 + p1

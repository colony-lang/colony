# Colony Types

## Bool: `bool`
```
x: bool = true
y := false
z := x && y
```

## Integer: `i*, u*, int`
```
x: i32 = 0i32
y := 100_000_i64
z := x + y                  // i64

w: int = 1                  // Arbitrary precision integer number
```

## Float: `f*, float`
```
x: f32 = 0.123_455_f32
y: f64 = 3.14f64
z := x + y                  // f64

w: float = 3.1415           // Arbitrary precision floating point number
```

## Bytes: `bytes, b'...'`
```
x: bytes = b'123abc'
y := b'\x00\x01\x02'
z := x + y
```

## String: `str, '...'`
```
x: str = '123abc'
y := 'AbcXyz789'
z := x + y
```

## List: `list, [n, ...]`
```
a: list = []
a = a.push(1)
a == [1]

b := [1, 2, '3', true]
```

## Dict: `dict, {k: v, ...}`
```
a: dict = {}
a = a.set('x', 0)

b := {'x': 0, .y: 1}
b = b.pop('y')
```

## Function: `fn, _ -> {}`
```
f: fn = x: i32 -> i32 {
    x + 1
}

g := x: i32 -> i32 {
    x + 1
}

h := x: i32 -> y: i32 -> i32 {
    x + y
}

unit := -> { _ }

a := f 1_i32
a == 2_i32

b := g 2_i32
b == 3_i32

h1: fn = h 1_i32
c: i32 = h1 2_i32

X: int = unit 1
X == 1
```

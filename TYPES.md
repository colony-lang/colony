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

## Tuple: `(k[: tv], ...)`
```
A := (x: int, y: int)
a: A = (0, 1)
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


a := f 1_i32
a == 2_i32

b := g 2_i32
b == 3_i32

h1: fn = h 1_i32
c: i32 = h1 2_i32
```

```
unit := -> { _ }
X: int = unit 1
X == 1
```

## Type
```
A: type = type 'A' [object] {
    .x: int(0),
    .y: int(0),

    .__add__: (self: A, other: A) -> A {
        res: A = {
            .x: self.x + other.x,
            .y: self.y + other.y,
        }

        res
    },

    add: (self: A, other: A) -> A {
        res: A = {
            .x: self.x + other.x,
            .y: self.y + other.y,
        }

        res
    },
}
```

```
a0: A = A(1, 1)
```

```
a1: A = A(2, 2)

a1.add = (self: A, other: A) -> A {
    res: A = {
        .x: self.x + other.x,
        .y: self.y + other.y,
    }

    res
}
```

```rust
Ok := type 'Ok' [object] {}
Error := type 'Error' [object] {}
Result := type 'Result' [Ok | Error] {}

AttributeError := type 'AttributeError' [Error] {}
AttributeResult := type 'AttributeResult' [Ok | AttributeError] {}

getattr := (obj: object, attr: str) -> Result {
    r: Result = obj.get(attr)

    match r |> typeof {
        Ok: -> {
            Ok(v) := r
            Ok(v)
        },
        Error: -> {
            Error(e) := r

            
        }
    }
}

t0 := getattr(a0, 'add')
```

```
a2 := a0.add(a1)
a2 == {.x: 3, .y: 3}
```

??? Attribute lookup: *Type* vs *Type Namespace* ???

```
???

// a2 := a0.__type_ns__.add(a0, a1)
a2 := a0.add(a1)
a2 == {.x: 3, .y: 3}

// a3 := a0.__type_ns__.__add__(a0, a1)
a3 := a0 + a1
a3 == {.x: 3, .y: 3}

a4 := A.__type_ns__.__add__(a0, a1)
a4 == {.x: 3, .y: 3}

???
```

```
X := type {.x: int(0)}
Y := type {.y: int(0)}

Z := X | Y

W := X & Y

W.__add__ = (self: W, other: W) -> W {
    res: W = {
        .x: self.x + other.x,
        .y: self.y + other.y,
    }

    res
}

z0: Z = X(1,)
z1: Z = Y(2,)

// w0: W = z0.__type__.__add__(z0, z1)
w0: W = z0 + z1

w1 := W(0, 1)
```


# Types

## Bool
```
b := true
b: bool = false
```

## Int
```
i := -1
i: int = -1
i: i8 = -1
i: i16 = -1
i: i32 = -1
i: i128 = -1
i: uint = 0
i: u8 = 0
```

## Float
```
f := 1.23
f: float = 1.23
f: f32 = 1.23
f: f64 = 1.23
```

## Bytes
```
b := b'h\x00e'
b := b"h\x00e"
b: bytes = b'h\x00e'
```

## String
```
s := 'Hello world'
s := "Hello world"
s: str = "Hello world"
```

## Tuple / MutTuple

Space: N
Get Index: O(1)
Get Key: O(N)
Set Index: O(N), copy with set
Set Key: O(N), copy with set
Mut Set Index: O(1)
Mut Set Key: O(N)

```
t := (-1, None, false, 1.1)
t[0] == -1
t[1] == None

T := (x: float, y: float=1.0)
t: T = (x: 1.0)
t: T = (x: 1.0, y: 2.0)

T := (x: float, y: float=1.0)
t: T = (-2, -1, 0, x=1.0, y=2.0, z: float=3.0, w: float=4.0)
t.__pfields__ == (-2, -1, 0)
t.__kwfields__ == (z: float=3.0, w: float=4.0)
t[0] == -2
t.x == 1.0
t.z == 3.0
```

## List / MutList

Space: N
Get Index: O(1)
Set Index: O(N), copy with set
Mut Set Index: O(1)

```
a: list = [-1, None, false, 1.1]
a := [-1, None, false, 1.1]

a[0] == -1
a[1] == None
```

## Dict / MutDict

Space: N (2/3 full), hash table, open addressing
Get Key: O(1)
Set Key: O(N), copy with set
Mut Set Key: O(1)

```
a := {'x': 1, .y: 2.0}
a: dict = {'x': 1, .y: 2.0}
a: dict[str, int | float] = {'x': 1, .y: 2.0}
a: dict[str, object] = {'x': 1, .y: 2.0}
a: dict[object, object] = {'x': 1, .y: 2.0}

a['x'] == 1
a['y'] == 2.0

a.x == 1
a.y == 2.0
```

## Function

Functions take single typed argument for a single typed parameter and return single typed value.

```
//
f := int -> int {
    _ + 1
}

r := f 1
r == 2

//
f: fn[int, int] = int -> int {
    _ + 1
}

r := f 1
r == 2

//
f := (x: float) -> float {
    x + 1
}

r := f (1,)
r == 2

//
f := (x: float,) -> float {
    x + 1
}

r := f (1,)
r == 2
```

## Object/Type Model

...

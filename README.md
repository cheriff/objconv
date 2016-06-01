# objconv

Convert obj files into binary representation suitable for quick opening and loading into OpenGL for display.

Also acts as a testbed for coming to terms with (modern?) c++ since I was taught "C with classes" 15 years ago. 
Advice/criticism is welcomed.

## File Format
General goals for the format:
 * Buffer can be mapped directly into OpenGL
 * Somewhat flexible
 
Intent is that updates to the format that don't break existing readers (currently just mingl) bump minor version, breaking changes increment major.
Ideally readers just check the major before proceeding.

### Version 1.1
Whoops, accidentally used 1.1 as first ever version. I guess that's where we'll start.

Just making sure geometry can be loaded and displayed properly.

File layout is:
 * Header
 * Attribute chunks: describes layout/stride/type of each data 'channel' present in buffer. Used for binding to shader attibutes
 * Group chunks: describes individually renderable subset of indices
 * Index list: array of index_count values, of the type specified by index_type. (may be 8/16/32 bits, depending on required range)
 * Buffer: buffsize bytes of data, mapped directly into VBO. Nomionally untyped, but format is (should be?) described by the attributes list.
 * EOF
 
Each section immedially follows the previous. Total file size should be given by: 

`sizeof(header) + header.num_attr*sizeof(attr) + header.num_groups*sizeof(group) + header.index_count * sizeof(header.index_type) + header.buffsize`

Undersized files are malformed, this can be checked by comparing actual filesize to result of the above formula before reading anything.
Oversized files will load, additional data will be ignored, readers may or may not warn.
#####Header:

| Type   | Name      | desc |
|--------|-----------|------|
|uint32_t|magic      | Constant value: 0x0B1EC701   |
|uint16_t|major      | Major version number: 1      |
|uint16_t|minor      | Minor version number: 1      |
|uint16_t|index_type | datatype of indices[1]       |
|uint16_t|index_count| number of indices            |
|uint32_t|buffsize   | Size in bytes of data buffer |
|char[16]|name       | Name of model (paded with \0, not necessarily null-terminated)|
|uint32_t|num_attrs  | Number of attributes present |
|uint32_t|num_groups | Number of mesh groups        |
Notes:

1. Currently allowed values: GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT

#####Attributes:

| Type   | Name      | desc |
|--------|-----------|------|
|char[16]| name      | Name of attribute, maps to shader input names |
|uint32_t| stride    | Stride between adjacent values[1]             |
|uint32_t| offset    | Offset from base of buffer of first values    |
|uint32_t| elem_type | Type of each element in the value[2]          |
|uint32_t| elem_count| Number of elements in each value[3]           |
Notes:

1. Currently unclear how to specify tightly-packed values. Setting `sizeof(value)` (alternatively `elem_count*sizeof(elem_type)`) is logical.
And OpenGL allows `0` to imply the same thing.
2. Currently allowed value: GL_FLOAT
3. Currently allowed values: 3 or 4 (i.e is a vector float3 or float4)

#####Groups:

| Type   | Name      | desc |
|--------|-----------|------|
|char[16]| name      | Name of Group    |
|uint16_t| base      | First index[1]   |
|uint16_t| count     | Number of indices, should be a multiple of 3 for drawing triangles |
Notes:

1. Currently specified as Nth index to start at, and NOT n bytes offset from base of array of indicies, as per OpenGL Api. This may change.

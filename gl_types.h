#ifndef __GL_TYPES_H__
#define __GL_TYPES_H__

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A

static inline const char *
gl_typeName(int type) {
    switch(type) {
        case GL_BYTE            : return "GL_BYTE";
        case GL_SHORT           : return "GL_SHORT";
        case GL_INT             : return "GL_INT";
        case GL_UNSIGNED_BYTE   : return "GL_UNSIGNED_BYTE";
        case GL_UNSIGNED_SHORT  : return "GL_UNSIGNED_SHORT";
        case GL_UNSIGNED_INT    : return "GL_UNSIGNED_INT";
        case GL_FLOAT           : return "GL_FLOAT";
        case GL_DOUBLE          : return "GL_DOUBLE";
        default                 : return "UNKNOWN";
    }
}

#endif // __GL_TYPES_H__

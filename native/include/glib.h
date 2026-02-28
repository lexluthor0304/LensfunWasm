#ifndef LFW_GLIB_COMPAT_H
#define LFW_GLIB_COMPAT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

#ifdef __cplusplus
#include <mutex>
extern "C" {
#endif

typedef int gboolean;
typedef int gint;
typedef unsigned int guint;
typedef uint32_t guint32;
typedef uint64_t guint64;
typedef size_t gsize;
typedef char gchar;
typedef unsigned char guchar;
typedef const void *gconstpointer;
typedef void *gpointer;
typedef uint32_t gunichar;
typedef double gdouble;
typedef float gfloat;
typedef ptrdiff_t gssize;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define GLIB_CHECK_VERSION(major, minor, micro) (1)
#define GLIB_VERSION_2_26 22600
#define GLIB_VERSION_2_32 23200
#define GLIB_VERSION_2_40 24000

typedef struct _GError
{
    gint domain;
    gint code;
    gchar *message;
} GError;

typedef struct _GString
{
    gchar *str;
    gsize len;
    gsize allocated_len;
} GString;

typedef struct _GPtrArray
{
    gpointer *pdata;
    guint len;
    guint allocated_len;
} GPtrArray;

typedef gint (*GCompareFunc)(gconstpointer a, gconstpointer b);
typedef void (*GDestroyNotify)(gpointer data);

typedef struct _GDir GDir;
typedef struct _GPatternSpec GPatternSpec;

typedef enum
{
    G_FILE_TEST_IS_DIR = 1 << 2
} GFileTest;

#define G_FILE_ERROR 1
#define G_FILE_ERROR_ACCES 13
#define G_FILE_ERROR_NOENT 2

typedef enum
{
    G_MARKUP_ERROR = 2,
    G_MARKUP_ERROR_INVALID_CONTENT = 3,
    G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE = 4
} GMarkupError;

typedef struct _GMarkupParseContext GMarkupParseContext;
typedef int GMarkupParseFlags;

typedef void (*GMarkupParserStartElementFunc)(
    GMarkupParseContext *context,
    const gchar *element_name,
    const gchar **attribute_names,
    const gchar **attribute_values,
    gpointer user_data,
    GError **error);

typedef void (*GMarkupParserEndElementFunc)(
    GMarkupParseContext *context,
    const gchar *element_name,
    gpointer user_data,
    GError **error);

typedef void (*GMarkupParserTextFunc)(
    GMarkupParseContext *context,
    const gchar *text,
    gsize text_len,
    gpointer user_data,
    GError **error);

typedef void (*GMarkupParserPassthroughFunc)(
    GMarkupParseContext *context,
    const gchar *passthrough_text,
    gsize text_len,
    gpointer user_data,
    GError **error);

typedef void (*GMarkupParserErrorFunc)(
    GMarkupParseContext *context,
    GError *error,
    gpointer user_data);

typedef struct _GMarkupParser
{
    GMarkupParserStartElementFunc start_element;
    GMarkupParserEndElementFunc end_element;
    GMarkupParserTextFunc text;
    GMarkupParserPassthroughFunc passthrough;
    GMarkupParserErrorFunc error;
} GMarkupParser;

#ifdef __cplusplus
typedef struct _GMutex
{
    std::mutex lock;
} GMutex;

typedef struct _GStaticMutex
{
    std::mutex lock;
} GStaticMutex;
#else
typedef struct _GMutex
{
    int unused;
} GMutex;

typedef struct _GStaticMutex
{
    int unused;
} GStaticMutex;
#endif

#define G_STATIC_MUTEX_INIT {}

#define g_new(type, count) ((type *)g_malloc(sizeof(type) * (count)))
#define g_ptr_array_index(array, index_) ((array)->pdata[(index_)])

void g_assertion_message(const char *expr, const char *file, int line);
#define g_assert(expr) ((expr) ? (void)0 : g_assertion_message(#expr, __FILE__, __LINE__))

void *g_malloc(gsize n_bytes);
void *g_realloc(gpointer mem, gsize n_bytes);
void g_free(gpointer mem);
gchar *g_strdup(const gchar *str);

void g_mutex_lock(GMutex *mutex);
void g_mutex_unlock(GMutex *mutex);
void g_static_mutex_lock(GStaticMutex *mutex);
void g_static_mutex_unlock(GStaticMutex *mutex);

gchar *g_build_filename(const gchar *first_element, ...);
const gchar *g_get_user_data_dir(void);

int g_open(const char *filename, int flags, int mode);

gboolean g_file_test(const gchar *filename, GFileTest test);
gboolean g_file_get_contents(const gchar *filename, gchar **contents, gsize *length, GError **error);

GDir *g_dir_open(const gchar *path, guint flags, GError **error);
const gchar *g_dir_read_name(GDir *dir);
void g_dir_close(GDir *dir);

GPatternSpec *g_pattern_spec_new(const gchar *pattern);
gboolean g_pattern_match(GPatternSpec *pspec, gsize string_length, const gchar *string, const gchar *string_reversed);
void g_pattern_spec_free(GPatternSpec *pspec);

GString *g_string_sized_new(gsize dfl_size);
GString *g_string_append(GString *string, const gchar *val);
gchar *g_string_free(GString *string, gboolean free_segment);

GPtrArray *g_ptr_array_new(void);
void g_ptr_array_set_size(GPtrArray *array, gint length);
gpointer *g_ptr_array_free(GPtrArray *array, gboolean free_segment);

void g_warning(const gchar *format, ...);
void g_set_error(GError **err, gint domain, gint code, const gchar *format, ...);

gunichar g_utf8_get_char(const gchar *p);
const gchar *g_utf8_next_char(const gchar *p);
gchar *g_utf8_casefold(const gchar *str, gssize len);
gboolean g_unichar_isspace(gunichar c);
gunichar g_unichar_tolower(gunichar c);

GMarkupParseContext *g_markup_parse_context_new(const GMarkupParser *parser, GMarkupParseFlags flags, gpointer user_data, GDestroyNotify user_data_dnotify);
gboolean g_markup_parse_context_parse(GMarkupParseContext *context, const gchar *text, gssize text_len, GError **error);
void g_markup_parse_context_free(GMarkupParseContext *context);
const gchar *g_markup_parse_context_get_element(GMarkupParseContext *context);
void g_markup_parse_context_get_position(GMarkupParseContext *context, gint *line_number, gint *char_number);

gchar *g_markup_vprintf_escaped(const gchar *format, va_list args);
gchar *g_markup_printf_escaped(const gchar *format, ...);

#ifdef __cplusplus
}
#endif

#endif

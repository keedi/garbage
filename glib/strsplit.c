#include <glib.h>

static void
strsplit_test1 (const gchar *str)
{
  gchar **tokens;
  gchar **ptr;

  tokens = g_strsplit (str, "//", 2);
  ptr = tokens;
  while (*ptr)
    {
      g_debug ("token: [%s]", *ptr);
      ++ptr;
    }

  g_strfreev (tokens);
}

static void
strsplit_test2 (const gchar *str)
{
  gchar **tokens;
  gchar **ptr;

  tokens = g_strsplit (str, "/", 2);
  ptr = tokens;
  while (*ptr)
    {
      g_debug ("token: [%s]", *ptr);
      ++ptr;
    }

  g_strfreev (tokens);
}

int
main (int    argc,
      char **argv)
{
  strsplit_test1 ("http://192.168.0.30:80/onvif/services");
  strsplit_test2 ("192.168.0.30:80/onvif/services");

  return 0;
}

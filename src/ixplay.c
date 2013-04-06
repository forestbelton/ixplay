#define CINTERFACE
#define COBJMACROS

#include "iTunesCOMInterface.h"
#include "xchat-plugin.h"

/* Plugin metadata. */
#define PLUGIN_NAME "iXPlay"
#define PLUGIN_DESC "Provides a pleasant interface towards retrieving playback"\
                    "information from iTunes"
#define PLUGIN_VERS "0.1"

/* Command metadata. */
#define IXNP_DESC "Usage: IXNP, Displays the currently playing song in iTunes."

static xchat_plugin *ph;
static IiTunes      *iITunes;

static int ix_nowplaying(char *word[], char *word_eol[], void *data) {
  IITTrack *track = NULL;
  BSTR     *name  = NULL;
  
  /* Get the currently playing track. */
  IiTunes_get_CurrentTrack(iITunes, &track);
  if(track == NULL) {
    xchat_print(ph, "iXPlay: There is no track currently playing.\n");
    return XCHAT_EAT_ALL;
  }
  
  IITTrack_get_Artist(track, name);
  xchat_printf(ph, "listening to %d", track == NULL);
  
  return XCHAT_EAT_ALL;
}

int xchat_plugin_init(xchat_plugin  *plugin_handle,
                      char         **plugin_name,
                      char         **plugin_desc,
                      char         **plugin_vers,
                      char          *arg) {
  /* Set XChat data. */
  ph           = plugin_handle;
  *plugin_name = PLUGIN_NAME;
  *plugin_desc = PLUGIN_DESC;
  *plugin_vers = PLUGIN_VERS;
  
  /* Initialize COM and create the iTunes COM instance. */
  CoInitialize(NULL);
  CoCreateInstance(&CLSID_iTunesApp, NULL, CLSCTX_LOCAL_SERVER,
                   &IID_IiTunes, (PVOID *)&iITunes);
  
  if(iITunes == NULL)
    return 0;
  
  /* Add hooks in XChat. */
  xchat_hook_command(ph, "ixnp", XCHAT_PRI_NORM, ix_nowplaying, IXNP_DESC, 0);
  
  xchat_print(ph, "iXPlay has been loaded.\n");
  return 1;
}

void xchat_plugin_get_info(char **name, char **desc, char **vers, void **unused)
{
  *name = PLUGIN_NAME;
  *desc = PLUGIN_DESC;
  *vers = PLUGIN_VERS;
}
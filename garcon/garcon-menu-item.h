/* vi:set et ai sw=2 sts=2 ts=2: */
/*-
 * Copyright (c) 2006-2010 Jannis Pohlmann <jannis@xfce.org>
 * Copyright (c) 2009      Nick Schermer <nick@xfce.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#if !defined(GARCON_INSIDE_GARCON_H) && !defined(GARCON_COMPILATION)
#error "Only <garcon/garcon.h> can be included directly. This file may disappear or change contents."
#endif

#ifndef __GARCON_MENU_ITEM_H__
#define __GARCON_MENU_ITEM_H__

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

typedef struct _GarconMenuItemPrivate GarconMenuItemPrivate;
typedef struct _GarconMenuItemClass   GarconMenuItemClass;
typedef struct _GarconMenuItem        GarconMenuItem;

#define GARCON_TYPE_MENU_ITEM            (garcon_menu_item_get_type())
#define GARCON_MENU_ITEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GARCON_TYPE_MENU_ITEM, GarconMenuItem))
#define GARCON_MENU_ITEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GARCON_TYPE_MENU_ITEM, GarconMenuItemClass))
#define GARCON_IS_MENU_ITEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GARCON_TYPE_MENU_ITEM))
#define GARCON_IS_MENU_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GARCON_TYPE_MENU_ITEM))
#define GARCON_MENU_ITEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GARCON_TYPE_MENU_ITEM, GarconMenuItemClass))

#ifndef XFCE_FIREJAIL_WIDGET_CONSTANTS
#define XFCE_FIREJAIL_WIDGET_CONSTANTS
/* Redefined here so non-GTK apps don't have to link to libxfce4ui */

typedef enum {
  FS_PRIV_NONE = 0,
  FS_PRIV_FULL = 1,
  FS_PRIV_READ_ONLY = 2,
  FS_PRIV_PRIVATE = 4
} FsPrivMode;

#define XFCE_FIREJAIL_RUN_IN_SANDBOX_KEY     "X-XfceSandboxWithFirejail"
#define XFCE_FIREJAIL_PROFILE_KEY            "X-XfceFirejailProfile"
#define XFCE_FIREJAIL_ENABLE_NETWORK_KEY     "X-XfceFirejailEnableNetwork"
#define XFCE_FIREJAIL_FS_MODE_KEY            "X-XfceFirejailFsMode"
#define XFCE_FIREJAIL_DISPOSABLE_KEY         "X-XfceFirejailOverlayDisposable"
#define XFCE_FIREJAIL_FS_SYNC_FOLDERS_KEY    "X-XfceFirejailSyncFolders"

#define XFCE_FIREJAIL_RUN_IN_SANDBOX_DEFAULT FALSE
#define XFCE_FIREJAIL_ENABLE_NETWORK_DEFAULT TRUE
#define XFCE_FIREJAIL_DISPOSABLE_DEFAULT     FALSE
#define XFCE_FIREJAIL_FS_MODE_DEFAULT        FS_PRIV_FULL
#endif

struct _GarconMenuItemClass
{
  GObjectClass __parent__;

  /* signals */
  void (*changed) (GarconMenuItem *item);
};

struct _GarconMenuItem
{
  GObject                  __parent__;

  /* < private > */
  GarconMenuItemPrivate *priv;
};



GType           garcon_menu_item_get_type                          (void) G_GNUC_CONST;

GarconMenuItem *garcon_menu_item_new                               (GFile           *file) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
GarconMenuItem *garcon_menu_item_new_for_path                      (const gchar     *filename) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;
GarconMenuItem *garcon_menu_item_new_for_uri                       (const gchar     *uri) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

gboolean        garcon_menu_item_reload                            (GarconMenuItem  *item,
                                                                    gboolean        *affects_the_outside,
                                                                    GError         **error);

gboolean        garcon_menu_item_reload_from_file                  (GarconMenuItem  *item,
                                                                    GFile           *file,
                                                                    gboolean        *affects_the_outside,
                                                                    GError         **error);

GFile          *garcon_menu_item_get_file                          (GarconMenuItem  *item);

gchar          *garcon_menu_item_get_uri                           (GarconMenuItem  *item) G_GNUC_MALLOC G_GNUC_WARN_UNUSED_RESULT;

const gchar    *garcon_menu_item_get_desktop_id                    (GarconMenuItem  *item);
void            garcon_menu_item_set_desktop_id                    (GarconMenuItem  *item,
                                                                    const gchar     *desktop_id);

const gchar    *garcon_menu_item_get_command                       (GarconMenuItem  *item);
void            garcon_menu_item_set_command                       (GarconMenuItem  *item,
                                                                    const gchar     *command);
const gchar    *garcon_menu_item_get_try_exec                      (GarconMenuItem  *item);
void            garcon_menu_item_set_try_exec                      (GarconMenuItem  *item,
                                                                    const gchar     *try_exec);
const gchar    *garcon_menu_item_get_name                          (GarconMenuItem  *item);
void            garcon_menu_item_set_name                          (GarconMenuItem  *item,
                                                                    const gchar     *name);
const gchar    *garcon_menu_item_get_generic_name                  (GarconMenuItem  *item);
void            garcon_menu_item_set_generic_name                  (GarconMenuItem  *item,
                                                                    const gchar     *generic_name);
const gchar    *garcon_menu_item_get_comment                       (GarconMenuItem  *item);
void            garcon_menu_item_set_comment                       (GarconMenuItem  *item,
                                                                    const gchar     *comment);
const gchar    *garcon_menu_item_get_icon_name                     (GarconMenuItem  *item);
void            garcon_menu_item_set_icon_name                     (GarconMenuItem  *item,
                                                                    const gchar     *icon_name);
const gchar    *garcon_menu_item_get_path                          (GarconMenuItem  *item);
void            garcon_menu_item_set_path                          (GarconMenuItem  *item,
                                                                    const gchar     *path);
gboolean        garcon_menu_item_get_hidden                        (GarconMenuItem  *item);
void            garcon_menu_item_set_hidden                        (GarconMenuItem  *item,
                                                                    gboolean         hidden);
gboolean        garcon_menu_item_requires_terminal                 (GarconMenuItem  *item);
void            garcon_menu_item_set_requires_terminal             (GarconMenuItem  *item,
                                                                    gboolean         requires_terminal);
gboolean        garcon_menu_item_get_no_display                    (GarconMenuItem  *item);
void            garcon_menu_item_set_no_display                    (GarconMenuItem  *item,
                                                                    gboolean         no_display);
gboolean        garcon_menu_item_supports_startup_notification     (GarconMenuItem  *item);
void            garcon_menu_item_set_supports_startup_notification (GarconMenuItem  *item,
                                                                    gboolean         supports_startup_notification);
GList          *garcon_menu_item_get_categories                    (GarconMenuItem  *item);
void            garcon_menu_item_set_categories                    (GarconMenuItem  *item,
                                                                    GList           *categories);
gboolean        garcon_menu_item_has_category                      (GarconMenuItem  *item,
                                                                    const gchar     *category);
gboolean        garcon_menu_item_get_show_in_environment           (GarconMenuItem  *item);
gboolean        garcon_menu_item_only_show_in_environment          (GarconMenuItem  *item);
void            garcon_menu_item_ref                               (GarconMenuItem  *item);
void            garcon_menu_item_unref                             (GarconMenuItem  *item);
gint            garcon_menu_item_get_allocated                     (GarconMenuItem  *item);
void            garcon_menu_item_increment_allocated               (GarconMenuItem  *item);
void            garcon_menu_item_decrement_allocated               (GarconMenuItem  *item);

gboolean        garcon_menu_item_get_sandboxed                     (GarconMenuItem  *item);
void            garcon_menu_item_set_sandboxed                     (GarconMenuItem  *item,
                                                                    gboolean         sandboxed);

const gchar    *garcon_menu_item_get_sandbox_profile               (GarconMenuItem  *item);
void            garcon_menu_item_set_sandbox_profile               (GarconMenuItem  *item,
                                                                    const gchar     *profile);

gboolean        garcon_menu_item_get_sandbox_enable_network        (GarconMenuItem  *item);
void            garcon_menu_item_set_sandbox_enable_network        (GarconMenuItem  *item,
                                                                    gboolean         sandbox_enable_network);

gint            garcon_menu_item_get_sandbox_fs_mode               (GarconMenuItem  *item);
void            garcon_menu_item_set_sandbox_fs_mode               (GarconMenuItem  *item,
                                                                    gint             sandbox_fs_mode);

gboolean        garcon_menu_item_get_sandbox_fs_disposable         (GarconMenuItem  *item);
void            garcon_menu_item_set_sandbox_fs_disposable         (GarconMenuItem  *item,
                                                                    gboolean         sandbox_fs_disposable);

gchar **        garcon_menu_item_get_sandbox_fs_sync_folders       (GarconMenuItem  *item);
void            garcon_menu_item_set_sandbox_fs_sync_folders       (GarconMenuItem  *item,
                                                                    gchar **         sandbox_fs_sync_folders);

gchar *         garcon_menu_item_expand_command                    (GarconMenuItem  *item,
                                                                    const gchar     *command_line);

G_END_DECLS

#endif /* !__GARCON_MENU_ITEM_H__ */

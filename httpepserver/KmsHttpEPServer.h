/*
 * Copyright (C) 2013 Kurento
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* inclusion guard */
#ifndef __KMS_HTTP_EP_SERVER_H__
#define __KMS_HTTP_EP_SERVER_H__

#include <gst/gst.h>
#include <glib-object.h>

/*
 * Type macros.
 */
#define KMS_TYPE_HTTP_EP_SERVER (            \
  kms_http_ep_server_get_type ()             \
)

#define KMS_HTTP_EP_SERVER(obj) (            \
  G_TYPE_CHECK_INSTANCE_CAST (               \
    (obj),                                   \
    KMS_TYPE_HTTP_EP_SERVER,                 \
    KmsHttpEPServer                          \
  )                                          \
)

#define KMS_IS_HTTP_EP_SERVER(obj) (         \
  G_TYPE_CHECK_INSTANCE_TYPE (               \
    (obj),                                   \
    KMS_TYPE_HTTP_EP_SERVER                  \
  )                                          \
)

#define KMS_HTTP_EP_SERVER_CLASS(klass) (    \
  G_TYPE_CHECK_CLASS_CAST (                  \
    (klass),                                 \
    KMS_TYPE_HTTP_EP_SERVER,                 \
    KmsHttpEPServerClass                     \
  )                                          \
)

#define KMS_IS_HTTP_EP_SERVER_CLASS(klass) ( \
  G_TYPE_CHECK_CLASS_TYPE (                  \
    (klass),                                 \
    KMS_TYPE_HTTP_EP_SERVER                  \
  )                                          \
)

#define KMS_HTTP_EP_SERVER_GET_CLASS(obj) (  \
  G_TYPE_INSTANCE_GET_CLASS (                \
    (obj),                                   \
    KMS_TYPE_HTTP_EP_SERVER,                 \
    KmsHttpEPServerClass)                    \
)

#define KMS_HTTP_EP_SERVER_ERROR \
  g_quark_from_static_string("kms-http-ep-server-error-quark")

typedef enum
{
  HTTPEPSERVER_RESOLVE_CANCELED_ERROR,
  HTTPEPSERVER_CANT_RESOLVE_ERROR,
  HTTPEPSERVER_UNEXPECTED_ERROR
} HttpEPServerError;

typedef struct _KmsHttpEPServer KmsHttpEPServer;
typedef struct _KmsHttpEPServerClass KmsHttpEPServerClass;
typedef struct _KmsHttpEPServerPrivate KmsHttpEPServerPrivate;

typedef void (*KmsHttpEPServerStartCallback) (KmsHttpEPServer * self,
    GError * err);

struct _KmsHttpEPServer
{
  GObject parent_instance;

  /* instance members */

  /*< private > */
  KmsHttpEPServerPrivate *priv;
};

struct _KmsHttpEPServerClass
{
  GObjectClass parent_class;

  /* public virtual methods */
  void (*start) (KmsHttpEPServer * self, KmsHttpEPServerStartCallback);
  void (*stop) (KmsHttpEPServer * self);
  const gchar *(*register_end_point) (KmsHttpEPServer * self, gpointer data,
      GDestroyNotify destroy);

  /* signal callbacks */
  void (*url_removed) (KmsHttpEPServer * self, gchar * url);
};

/* used by KMS_TYPE_HTTP_EP_SERVER */
GType kms_http_ep_server_get_type (void);

/* Virtual public methods */
KmsHttpEPServer *kms_http_ep_server_new (const char *optname1, ...);
void kms_http_ep_server_start (KmsHttpEPServer * self,
    KmsHttpEPServerStartCallback start_cb);
void kms_http_ep_server_stop (KmsHttpEPServer * self);
const gchar *kms_http_ep_server_register_end_point (KmsHttpEPServer * self,
    gpointer data, GDestroyNotify destroy);

#define KMS_HTTP_EP_SERVER_PORT "port"
#define KMS_HTTP_EP_SERVER_INTERFACE "interface"

#endif /* __KMS_HTTP_EP_SERVER_H__ */

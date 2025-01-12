//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// The contents of this file must follow a specific format in order to
// support the CEF translator tool. See the translator.README.txt file in the
// tools directory for more information.
//

#ifndef CEF_INCLUDE_CEF_MEDIA_ACCESS_HANDLER_H_
#define CEF_INCLUDE_CEF_MEDIA_ACCESS_HANDLER_H_
#pragma once

#include "include/cef_base.h"
#include "include/cef_browser.h"

///
// Represents the state of a setting.
///
/*--cef()--*/
typedef enum {
  ///
  // No permission
  ///
  CEF_MEDIA_PERMISSION_NONE = 0,

  ///
  // Audio capture permission
  ///
  CEF_MEDIA_PERMISSION_DEVICE_AUDIO_CAPTURE = 1 << 0,

  ///
  // Video capture permission
  ///
  CEF_MEDIA_PERMISSION_DEVICE_VIDEO_CAPTURE = 1 << 1,

  ///
  // Desktop audio capture permission
  ///
  CEF_MEDIA_PERMISSION_DESKTOP_AUDIO_CAPTURE = 1 << 2,

  ///
  // Desktop video capture permission
  ///
  CEF_MEDIA_PERMISSION_DESKTOP_VIDEO_CAPTURE = 1 << 3,
} cef_media_access_permission_types_t;

///
// Callback interface used for asynchronous continuation of media access
// permission requests.
///
/*--cef(source=library)--*/
class CefMediaAccessCallback : public virtual CefBaseRefCounted {
 public:
  ///
  // Call to allow or deny media access.
  // If this callback was initiated in response to a getUserMedia (indicated by
  // CEF_MEDIA_PERMISSION_DEVICE_AUDIO_CAPTURE and/or
  // CEF_MEDIA_PERMISSION_DEVICE_VIDEO_CAPTURE being set) the
  // |allowed_permissions| are required to match those given in
  // |required_permissions| in the OnRequestMediaAccessPermission.
  ///
  /*--cef(capi_name=cont)--*/
  virtual void Continue(int allowed_permissions) = 0;

  ///
  // Cancel the media access request.
  ///
  /*--cef()--*/
  virtual void Cancel() = 0;
};

///
// Implement this interface to handle events related to media access permission
// requests. The methods of this class will be called on the browser process UI
// thread.
///
/*--cef(source=client)--*/
class CefMediaAccessHandler : public virtual CefBaseRefCounted {
 public:
  ///
  // Called when a page requests permission to access media.
  // |requesting_url| is the URL requesting permission. Return true and call
  // CefMediaAccessCallback::Continue() either in this method or at a later
  // time to continue or cancel the request. Return false to cancel the request
  // immediately.
  ///
  /*--cef()--*/
  virtual bool OnRequestMediaAccessPermission(
      CefRefPtr<CefBrowser> browser,
      CefRefPtr<CefFrame> frame,
      const CefString& requesting_url,
      int32_t requested_permissions,
      CefRefPtr<CefMediaAccessCallback> callback) {
    return false;
  }
};

#endif  // CEF_INCLUDE_CEF_MEDIA_ACCESS_HANDLER_H_

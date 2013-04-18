{
  "targets": [
    {
      "target_name": "houdini",
      "product_prefix": "lib",
      "type": "static_library",
      "include_dirs": [ "./houdini" ],
      "sources": [ "houdini/buffer.c" , "houdini/houdini_href_e.c" , "houdini/houdini_html_e.c" , "houdini/houdini_html_u.c" , "houdini/houdini_js_e.c" , "houdini/houdini_js_u.c" , "houdini/houdini_uri_e.c" , "houdini/houdini_uri_u.c" , "houdini/houdini_xml_e.c" ]
    },
    {
      "target_name": "bindings",
      "include_dirs": [ "houdini/" ],
      "dependencies": [ "houdini" ],
      "sources": [ "bindings.cc" ]
    }
  ]
}

# node-houdini

> Node.js bindings for [Houdini](https://github.com/zacharyvoase/houdini), a text escaping library by GitHub.

**Bundled Houdini version:** [e6f0ec96b85578a2fd8ab79af84493cad3a84cfb](https://github.com/vmg/houdini/commit/e6f0ec96b85578a2fd8ab79af84493cad3a84cfb)

From [Houdini's README](https://github.com/zacharyvoase/houdini/blob/master/README.md):

Houdini is a simple API for escaping text for the web. And unescaping it. But that kind of breaks the joke in the name so nevermind.

- HTML escaping follows the OWASP suggestion. All other entities are left as-is.

        & --> &amp;
        < --> &lt;
        > --> &gt;
        " --> &quot;
        ' --> &#x27;     &apos; is not recommended
        / --> &#x2F;     forward slash is included as it helps end an HTML entity

- HTML unescaping is fully RFC-compliant. Yes, that's the 253 different entities for you, and decimal/hex code point specifiers.

- URI escaping and unescaping is fully RFC-compliant.

- URL escaping and unescaping is the same as generic URIs, but spaces are changed to `+`.

## Warning

1. This is my first Node.js addon and C++ isn't my mother tongue.
2. It is still in version 0.1.0, do not rely too much on it for production purpose, and be aware that the API might change at any time.

This module follows [Semver](http://semver.org).

## Installation
    
    $ npm install -g node-gyp
    $ npm install houdini

## Usage

> I'm not really happy with the current API, and am therefore [open to suggestions](https://github.com/romac/node-houdini/issues).  

```js
var houdini = require('houdini'),
    escaped;

escaped = houdini.escapeHTML( str, secure = true );
houdini.unescapeHTML( escaped ) === str;

escaped = houdini.escapeXML( str );

escaped = houdini.escapeURI( str );
houdini.unescapeURI( str ) === str;

escaped = houdini.escapeURL( str );
houdini.unescapeURL( str ) === str;

escaped = houdini.escapeHREF( str );

escaped = houdini.escapeJS( str );
houdini.unescapeJS( str ) === str;
```

## License

node-houdini is released under the [MIT license](http://romac.mit-license.org).
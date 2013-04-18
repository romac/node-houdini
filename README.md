
# node-houdini [![Dependencies Status](https://david-dm.org/romac/node-houdini.png)](https://david-dm.org/romac/node-houdini)

> Node.js bindings for [Houdini](https://github.com/vmg/houdini), a text escaping library by GitHub.

**Bundled Houdini version:** [e6f0ec96b85578a2fd8ab79af84493cad3a84cfb](https://github.com/vmg/houdini/commit/e6f0ec96b85578a2fd8ab79af84493cad3a84cfb)

From [Houdini's README](https://github.com/vmg/houdini#readme):

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

## Installation

    $ npm install -g node-gyp
    $ npm install houdini

## Usage

```js
var houdini = require('houdini');

var str = 'A & B > C';

var escaped = houdini.escapeHTML(str); // A &amp; B &gt; C

var unescaped = houdini.unescapeHTML(escaped); // A & B > C
```

## Methods

All the methods return the (un)escaped string.

### .escapeHTML(str, secure = false)
### .unescapeHTML(str)
### .escapeXML(str)
### .escapeURL(str)
### .unescapeURL(str)
### .escapeURI(str)
### .unescapeURI(str)
### .escapeHREF(str)
### .escapeJS(str)
### .unescapeJS(str)

## License

node-houdini is released under the [MIT license](http://romac.mit-license.org).
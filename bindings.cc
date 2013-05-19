
#include <v8.h>
#include <node.h>
#include <iostream>

#include "houdini.h"

using namespace v8;
using namespace node;

namespace houdini
{

#define HOUDINI_FUNCTION_HEADER( name ) \
    Handle<Value> name( const Arguments &args ) { \
    HandleScope scope; \
    \
    if( args.Length() < 1 ) \
    { \
        ThrowException( Exception::TypeError( String::New( "First argument is mandatory" ) ) ); \
        return scope.Close( Undefined() ); \
    } \
    \
    if( !args[ 0 ]->IsString() ) \
    { \
        ThrowException( Exception::TypeError( String::New( "First argument must be of type 'string'" ) ) ); \
        return scope.Close( Undefined() ); \
    } \
    \
    Local<String> string = args[ 0 ]->ToString(); \
    v8::String::Utf8Value input( string ); \
    \
    gh_buf buffer = GH_BUF_INIT;

#define HOUDINI_FUNCTION_FOOTER() \
}

#define HOUDINI_FUNCTION( name ) \
    HOUDINI_FUNCTION_HEADER( name ) \
    if( houdini_##name( &buffer, ( const unsigned char * )( *input ), input.length() ) ) \
    { \
        return scope.Close( String::New( buffer.ptr ) ); \
    } \
    \
    return scope.Close( string ); \
    HOUDINI_FUNCTION_FOOTER()


HOUDINI_FUNCTION_HEADER( escape_html0 )
    int secure = args.Length() > 1 ? ( int )args[ 1 ]->ToBoolean()->Value() : 1;
    if( houdini_escape_html0( &buffer, ( const unsigned char * )( *input ), input.length(), secure ) ) \
    {
        return scope.Close( String::New( buffer.ptr ) );
    }
    return scope.Close( string );
HOUDINI_FUNCTION_FOOTER()

HOUDINI_FUNCTION( unescape_html )

HOUDINI_FUNCTION( escape_xml )

HOUDINI_FUNCTION( escape_uri )
HOUDINI_FUNCTION( unescape_uri )

HOUDINI_FUNCTION( escape_url )
HOUDINI_FUNCTION( unescape_url )

HOUDINI_FUNCTION( escape_href )

HOUDINI_FUNCTION( escape_js )
HOUDINI_FUNCTION( unescape_js )

extern "C" void init( Handle<Object> exports )
{
    NODE_SET_METHOD( exports, "escapeHTML", escape_html0 );
    NODE_SET_METHOD( exports, "unescapeHTML", unescape_html );
    NODE_SET_METHOD( exports, "escapeXML", escape_xml );
    NODE_SET_METHOD( exports, "escapeURI", escape_uri );
    NODE_SET_METHOD( exports, "unescapeURI", unescape_uri );
    NODE_SET_METHOD( exports, "escapeURL", escape_url );
    NODE_SET_METHOD( exports, "unescapeURL", unescape_url );
    NODE_SET_METHOD( exports, "escapeHREF", escape_href );
    NODE_SET_METHOD( exports, "escapeJS", escape_js );
    NODE_SET_METHOD( exports, "unescapeJS", unescape_js );
}

NODE_MODULE( houdini, init )

}

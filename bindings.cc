
#include <v8.h>
#include <node.h>
#include <iostream>

#include "houdini.h"

using namespace v8;
using namespace node;

#define CONCAT( x, y ) x##y
#define CPP_FUNCTION_NAME( name ) CONCAT( Houdini_, name )

#define HOUDINI_FUNCTION_HEADER( name ) \
    Handle<Value> CPP_FUNCTION_NAME(name)( const Arguments &args ) { \
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
    v8::String::Utf8Value utf8string( string ); \
    int length = utf8string.length(); \
    uint8_t *value = reinterpret_cast<uint8_t *>( *utf8string ); \
    \
    gh_buf buffer = GH_BUF_INIT;

#define HOUDINI_FUNCTION_FOOTER() \
}

#define HOUDINI_ESCAPE_FUNCTION( name ) \
    HOUDINI_FUNCTION_HEADER( escape_##name ) \
    if( CONCAT( houdini_escape_, name )( &buffer, value, length ) ) \
    { \
        Local<String> escaped = String::New( buffer.ptr ); \
        return scope.Close( escaped ); \
    } \
    return scope.Close( string ); \
HOUDINI_FUNCTION_FOOTER()

#define HOUDINI_UNESCAPE_FUNCTION( name ) \
    HOUDINI_FUNCTION_HEADER( unescape_##name ) \
    if( CONCAT( houdini_unescape_, name )( &buffer, value, length ) ) \
    { \
        Local<String> escaped = String::New( buffer.ptr ); \
        return scope.Close( escaped ); \
    } \
    return scope.Close( string ); \
HOUDINI_FUNCTION_FOOTER()

HOUDINI_FUNCTION_HEADER( escape_html0 )
    int secure = args.Length() > 1 ? ( int )args[ 1 ]->ToBoolean()->Value() : 1; \
    if( houdini_escape_html0( &buffer, value, length, secure ) ) \
    { \
        Local<String> escaped = String::New( buffer.ptr ); \
        return scope.Close( escaped ); \
    } \
    return scope.Close( string ); \
HOUDINI_FUNCTION_FOOTER()

HOUDINI_UNESCAPE_FUNCTION( html )

HOUDINI_ESCAPE_FUNCTION( xml )

HOUDINI_ESCAPE_FUNCTION( uri )
HOUDINI_UNESCAPE_FUNCTION( uri )

HOUDINI_ESCAPE_FUNCTION( url )
HOUDINI_UNESCAPE_FUNCTION( url )

HOUDINI_ESCAPE_FUNCTION( href )

HOUDINI_ESCAPE_FUNCTION( js )
HOUDINI_UNESCAPE_FUNCTION( js )

extern "C" void init( Handle<Object> exports )
{
    NODE_SET_METHOD( exports, "escapeHTML", CPP_FUNCTION_NAME( escape_html0 ) );
    NODE_SET_METHOD( exports, "unescapeHTML", CPP_FUNCTION_NAME( unescape_html ) );
    NODE_SET_METHOD( exports, "escapeXML", CPP_FUNCTION_NAME( escape_xml ) );
    NODE_SET_METHOD( exports, "escapeURI", CPP_FUNCTION_NAME( escape_uri ) );
    NODE_SET_METHOD( exports, "unescapeURI", CPP_FUNCTION_NAME( unescape_uri ) );
    NODE_SET_METHOD( exports, "escapeURL", CPP_FUNCTION_NAME( escape_url ) );
    NODE_SET_METHOD( exports, "unescapeURL", CPP_FUNCTION_NAME( unescape_url ) );
    NODE_SET_METHOD( exports, "escapeHREF", CPP_FUNCTION_NAME( escape_href ) );
    NODE_SET_METHOD( exports, "escapeJS", CPP_FUNCTION_NAME( escape_js ) );
    NODE_SET_METHOD( exports, "unescapeJS", CPP_FUNCTION_NAME( unescape_js ) );
}

NODE_MODULE( houdini, init )
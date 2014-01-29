#include<string>
#include<csl/CSLLocale/CSLLocale.h>

namespace csl {

    namespace JNIUtils {
	// get std::string from java string
	inline void jstringToString( JNIEnv*& env, jstring& jstr, std::string& str  ) {
	
	    char const* cstr = env->GetStringUTFChars( jstr, 0 );
	    str = cstr;
	    
	    env->ReleaseStringUTFChars( jstr, cstr );
	}
	
	inline void jstringToWstring( JNIEnv*& env, jstring& jstr, std::wstring& wstr  ) {
	    std::string str;
	    jstringToString( env, jstr, str);
	    CSLLocale::string2wstring( str, wstr );
	}


	/**
	 * @brief throws a JAVA exception of the given type with the given message
	 *
	 * taken from the JNI programmer's guide, p.75
	 */
	void throwExceptionByName( JNIEnv *env, char const* name, char const* msg ) {
	    jclass cls = env->FindClass( name );
	    /* If cls is NULL, an exception has already been thrown */
	    if (cls != NULL) {
		env->ThrowNew( cls, msg );
	    }
	    /* free the local ref */
	    env->DeleteLocalRef( cls );
	}
	



    }
}

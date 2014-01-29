#ifndef _Included_csl_DictSearch_DictSearch_cxx
#define _Included_csl_DictSearch_DictSearch_cxx _Included_csl_DictSearch_DictSearch_cxx

#include "./csl_DictSearch_DictSearch.h"
#include "./JNIUtils.h"
#include<csl/DictSearch/DictSearch.h>


/*
 * Class:     csl_DictSearch_DictSearch
 * Method:    native_init
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_csl_DictSearch_DictSearch_native_1init
(JNIEnv *env , jobject callerObj, jstring j_configFile ) {
    std::string configFile;

    try {
	csl::JNIUtils::jstringToString( env, j_configFile, configFile );
	csl::DictSearch* ds = new csl::DictSearch();
	ds->readConfiguration( configFile );
	return (jlong)ds;
    } catch( std::exception& exc ) {
	std::string what( "(JNI)Java_csl_DictSearch_DictSearch_native_1init: Caught exception: " );
	what.append( exc.what() );
	csl::JNIUtils::throwExceptionByName( env, "csl/DictSearch/DictSearchException", what.c_str() );
    }
    
}


/*
 * Class:     csl_DictSearch_DictSearch
 * Method:    native_query
 * Signature: (Ljava/lang/String;Lcsl/DictSearch/DictSearch/ResultReceiver;)J
 */
JNIEXPORT void JNICALL Java_csl_DictSearch_DictSearch_native_1query
(JNIEnv * env, jobject callerObj, jstring query , jobject resultReceiver ) {
    // get DictSearch object
    jclass dictSearchClass = env->GetObjectClass( callerObj );
    jfieldID pointerFieldID = env->GetFieldID( dictSearchClass, "pointer_", "J" );
    if( pointerFieldID == NULL ) {
	return; // GetFieldID has thrown an exception. Leave it to the caller to handle this.
    }
    
    csl::DictSearch* dictSearch = (csl::DictSearch*) env->GetLongField( callerObj, pointerFieldID);
    
    // get receiver method
    jclass receiverClass = env->GetObjectClass( resultReceiver );
    jmethodID methodID = env->GetMethodID( receiverClass, "receive", "(Ljava/lang/String;)V" );
    if( methodID == NULL ) {
	csl::JNIUtils::throwExceptionByName( env, "csl/DictSearch/DictSearchException", "Could not find receive method" );
	return;
    }

    std::wstring cpp_query;
    csl::JNIUtils::jstringToWstring( env, query, cpp_query );

    csl::DictSearch::CandidateSet cands;
    std::string cpp_cand;
    try {
	dictSearch->query( cpp_query, &cands );
    } catch( std::exception& exc ) {
	csl::JNIUtils::throwExceptionByName( env, "csl/DictSearch/DictSearchException", exc.what() );
	return;
    }
    for( csl::DictSearch::CandidateSet::const_iterator cand = cands.begin(); cand != cands.end(); ++cand ) {
    	csl::CSLLocale::wstring2string( cand->toString(), cpp_cand );
	
    	env->CallVoidMethod( resultReceiver, methodID, env->NewStringUTF( cpp_cand.c_str() ) );
    }
    

}



#endif

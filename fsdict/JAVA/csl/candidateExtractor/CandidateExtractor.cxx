#ifndef _Included_CandExtractor_CXX
#define _Included_CandExtractor_CXX

#include "./CandidateExtractor.h"

#include "../../../Global.h"
#include "../../../MSMatch/MSMatch.h"
#include "../../../ResultSet/ResultSet.h"




JNIEXPORT void JNICALL Java_csl_candidateExtractor_CandidateExtractor_initNativeCandExtractor
( JNIEnv* env, jobject callerObj, jint levDistance, jstring dicFile, jstring revDicFile ) {
    jclass callerClass = env->GetObjectClass( callerObj );

    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );

    fsdict::MSMatch<fsdict::FW_BW>* msMatch = new fsdict::MSMatch< fsdict::FW_BW >( levDistance, env->GetStringUTFChars( dicFile, 0 ), env->GetStringUTFChars( revDicFile, 0 ) );

    env->SetLongField( callerObj, msMatchPointerID, (unsigned long)msMatch );
}

JNIEXPORT void JNICALL Java_csl_candidateExtractor_CandidateExtractor_destroyNativeCandExtractor
( JNIEnv* env, jobject callerObj ) {
    jclass callerClass = env->GetObjectClass( callerObj );
    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );
    
    // delete the MSMatch-object
    delete( (fsdict::MSMatch<fsdict::FW_BW>*)env->GetLongField( callerObj, msMatchPointerID ) );
}


JNIEXPORT void JNICALL Java_csl_candidateExtractor_CandidateExtractor_nativeQuery
( JNIEnv* env, jobject callerObj, jstring pattern, jint levDistance, jobject receiverObj ) {
    // get MSMatch-object
    jclass callerClass = env->GetObjectClass( callerObj );
    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );
    fsdict::MSMatch<fsdict::FW_BW>* msMatch = (fsdict::MSMatch<fsdict::FW_BW>*)env->GetLongField( callerObj, msMatchPointerID );

    // get the receiver-method. Here, type-safety is somewhat gone: whatever class has a suitable method receive(...) will do
    jclass receiverClass = env->GetObjectClass( receiverObj );
    jmethodID receiveID = env->GetMethodID( receiverClass, "receive", "(Ljava/lang/String;FF)V" );

    fsdict::ResultSet* resultSet = new fsdict::ResultSet();

    // get wcstring from java string
    wchar_t wcsPattern[fsdict::Global::lengthOfLongStr];
    const fsdict::uchar* utf8Pattern = (const fsdict::uchar*) env->GetStringUTFChars( pattern, 0 );
    mbstowcs( wcsPattern, (char*)utf8Pattern, fsdict::Global::lengthOfLongStr );
    env->ReleaseStringUTFChars( pattern, (char*)utf8Pattern );
    
    msMatch->query( wcsPattern, *resultSet );

    fsdict::uchar mbsResult[fsdict::Global::lengthOfLongStr];
    for( size_t i = 0; i < resultSet->getSize(); ++i ) {
	wcstombs( (char*)mbsResult, (*resultSet)[i].getStr(), fsdict::Global::lengthOfLongStr );
	jstring javaStr = env->NewStringUTF( (char*)mbsResult ); 
	env->CallVoidMethod( receiverObj, receiveID, javaStr, (jfloat)( (*resultSet)[i].getLevDistance() ), (jfloat)( (*resultSet)[i].getAnn() ) );
	env->ReleaseStringUTFChars( javaStr, 0 );
    }

    delete( resultSet );

}


JNIEXPORT jboolean JNICALL Java_csl_candidateExtractor_CandidateExtractor_nativeLookup
( JNIEnv* env, jobject callerObj, jstring pattern ) {
    // get MSMatch-object
    jclass callerClass = env->GetObjectClass( callerObj );
    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );
    fsdict::MSMatch<fsdict::FW_BW>* msMatch = (fsdict::MSMatch<fsdict::FW_BW>*)env->GetLongField( callerObj, msMatchPointerID );

    // get wcstring from java string
    wchar_t wcsPattern[fsdict::Global::lengthOfLongStr];
    const fsdict::uchar* utf8Pattern = (const fsdict::uchar*) env->GetStringUTFChars( pattern, 0 );
    mbstowcs( wcsPattern, (char*)utf8Pattern, fsdict::Global::lengthOfLongStr );
    env->ReleaseStringUTFChars( pattern, (char*)utf8Pattern );

    const fsdict::MinDic& dic = msMatch->getFWDic();
    
    uint dicpos = dic.walkStr( dic.getRoot(), wcsPattern );
    if( dicpos && dic.isFinal( dicpos ) ) {
	return 1;
    }
    else return 0;
}


// not used 
JNIEXPORT void JNICALL Java_CandExtractor_test
(JNIEnv * env, jobject caller, jobject caExObject ) {
    printf( "c++ says: test ...\n" );
    jclass caExClass = env->GetObjectClass( caExObject );
    jmethodID ceTest = env->GetMethodID( caExClass, "sayJuhuu", "()V" );
    
    env->CallVoidMethod( caExObject, ceTest );
}

#endif

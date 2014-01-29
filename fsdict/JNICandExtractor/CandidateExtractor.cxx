#ifndef _Included_CandExtractor_CXX
#define _Included_CandExtractor_CXX

#include "./CandExtractor.h"
#include "../MSMatch/MSMatch.h"
#include "../ResultSet/ResultSet.h"




JNIEXPORT void JNICALL Java_CandExtractor_initNativeCandExtractor
( JNIEnv* env, jobject callerObj, jstring alphFile, jint levDistance, jstring dicFile, jstring revDicFile ) {
    jclass callerClass = env->GetObjectClass( callerObj );

    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );
    jfieldID alphPointerID = env->GetFieldID( callerClass, "alphPointer_", "J" );

    printf( "Enter initNativeCandExtractor\n" );
    fsdict::Alphabet* alph = new fsdict::Alphabet( env->GetStringUTFChars( alphFile, 0 ) );
    fsdict::MSMatch<fsdict::FW_BW>* msMatch = new fsdict::MSMatch<fsdict::FW_BW>( *alph, levDistance, env->GetStringUTFChars( dicFile, 0 ), env->GetStringUTFChars( revDicFile, 0 ) );

    env->SetLongField( callerObj, msMatchPointerID, (unsigned long)msMatch );
    env->SetLongField( callerObj, alphPointerID, (unsigned long)alph );
    printf( "Leave init\n" );
}

JNIEXPORT void JNICALL Java_CandExtractor_destroyNativeCandExtractor
( JNIEnv* env, jobject callerObj ) {
    jclass callerClass = env->GetObjectClass( callerObj );
    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );
    jfieldID alphPointerID = env->GetFieldID( callerClass, "alphPointer_", "J" );
    
    // delete the alph and MSMatch-object
    delete( (fsdict::MSMatch<fsdict::FW_BW>*)env->GetLongField( callerObj, msMatchPointerID ) );
    delete( (fsdict::Alphabet*)env->GetLongField( callerObj, alphPointerID ) );
}

JNIEXPORT void JNICALL Java_CandExtractor_nativeQuery
( JNIEnv* env, jobject callerObj, jstring pattern, jint levDistance, jobject receiverObj ) {
    printf( "Enter query\n" );
    // get MSMatch-object and alph-object
    jclass callerClass = env->GetObjectClass( callerObj );
    jfieldID msMatchPointerID = env->GetFieldID( callerClass, "msMatchPointer_", "J" );
    jfieldID alphPointerID = env->GetFieldID( callerClass, "alphPointer_", "J" );
    fsdict::MSMatch<fsdict::FW_BW>* msMatch = (fsdict::MSMatch<fsdict::FW_BW>*)env->GetLongField( callerObj, msMatchPointerID );
    fsdict::Alphabet* alph = (fsdict::Alphabet*)env->GetLongField( callerObj, alphPointerID );

    // get the receiver-method
    jclass receiverClass = env->GetObjectClass( receiverObj );
    jmethodID receiveID = env->GetMethodID( receiverClass, "receive", "(Ljava/lang/String;FF)V" );

    fsdict::ResultSet* resultSet = new fsdict::ResultSet( *alph );

    msMatch->query( (fsdict::uchar*)( env->GetStringUTFChars( pattern, 0 ) ), *resultSet );

    for( size_t i = 0; i < resultSet->getSize(); ++i ) {
	jstring javaStr = env->NewStringUTF( (const char*)( (*resultSet)[i].getStr() ) ); 
	env->CallVoidMethod( receiverObj, receiveID, javaStr, (jfloat)2, (jfloat)( (*resultSet)[i].getAnn() ) );
	env->ReleaseStringUTFChars( javaStr, NULL );
    }

    delete( resultSet );
    printf( "Leave query\n" );

}

JNIEXPORT jboolean JNICALL Java_CandExtractor_lookup
( JNIEnv* env, jobject caller, jstring pattern, jobject frequency ) {
    return false;
}


JNIEXPORT void JNICALL Java_CandExtractor_test
(JNIEnv * env, jobject caller, jobject caExObject ) {
    printf( "c++ says: test ...\n" );
    jclass caExClass = env->GetObjectClass( caExObject );
    jmethodID ceTest = env->GetMethodID( caExClass, "sayJuhuu", "()V" );
    
    env->CallVoidMethod( caExObject, ceTest );
}

#endif

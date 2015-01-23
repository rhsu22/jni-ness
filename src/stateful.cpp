#include "jni.h"
#include <unordered_map>
#include <string>
#include <iostream>

/**
* Creates a hashtable on the heap, returns the pointer
*/
static jlong createHashTable(JNIEnv *env, jclass clazz) {

  std::cout << "Begin building map.\n";


  std::unordered_map<int, std::string> *map = new std::unordered_map<int, std::string>();

  map->insert(std::make_pair(0, "Hello world."));
  map->insert(std::make_pair(1, "I want to eat pizza."));
  map->insert(std::make_pair(2, "Let's go Mets."));
  map->insert(std::make_pair(3, "BigRed is working overtime."));
  map->insert(std::make_pair(4, "Why is the fan spinning?"));


  std::cout << "Finished building map.\n";

  return (jlong) map;
}

static void printHashTable(JNIEnv *env, jclass clazz, jlong tableAddr) {

  std::cout << "Begin printing table\n";

  std::unordered_map<int, std::string> *map = (std::unordered_map<int, std::string> *)tableAddr;

  for (auto& p : *map) {
    std::cout << p.second << std::endl;
  }

}


static JNINativeMethod methodsTable[] = {
        {const_cast<char *>("createHashTable"), const_cast<char *>("()J"), (void *) createHashTable},
        {const_cast<char *>("printHashTable"), const_cast<char *>("(J)V"), (void *) printHashTable}
};

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{

  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return -1;
  }
  else {
    jclass cla = env->FindClass("stateful");

    std::cout << "Registering functions.\n";
    env->RegisterNatives(cla, methodsTable, sizeof(methodsTable) / sizeof(methodsTable[0]));

    std::cout << "Finished registering function.\n";
  }

  // Get jclass with env->FindClass.
  // Register methods with env->RegisterNatives.

  return JNI_VERSION_1_6;
}
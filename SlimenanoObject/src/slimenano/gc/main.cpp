//
// Created by xzy54 on 25-6-2.
//
#include "slimenano/gc/GCObject.hpp"
#include "slimenano/gc/GarbageCollectorManager.hpp"

#define fun auto
#define val const auto
#define var auto

SLIMENANO_GC_CLASS(Person){

};

SLIMENANO_GC_CLASS(Student){

    SLIMENANO_GC_OBJECT(Person) person = slimenano::gc::GCObject<Person>::Null();

};

fun main() -> int {

    slimenano::gc::GarbageCollectorManager::Initialize();
    Student::New();

    return 0;
}
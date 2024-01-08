//
// Created by daiyi on 2020/03/23.
//

#include <fcntl.h>
#include <sys/stat.h>
#include "Vlog.h"
#include "util.h"
#include "util/coding.h"

using std::string;



const int buffer_size_max = 300 * 1024;

namespace adgMod {

VLog::VLog(const std::string& vlog_name) :
    writer(nullptr),
    reader(nullptr) {
    adgMod::env->NewWritableFile(vlog_name, &writer);
    adgMod::env->NewRandomAccessFile(vlog_name, &reader);
    buffer.reserve(buffer_size_max * 2);
    struct ::stat file_stat;
    ::stat(vlog_name.c_str(), &file_stat);
    vlog_size = file_stat.st_size;
}

uint64_t VLog::AddRecord(const Slice& key, const Slice& value) {
    PutLengthPrefixedSlice(&buffer, key);
    PutVarint32(&buffer, value.size());
    uint64_t result = vlog_size + buffer.size();
    buffer.append(value.data(), value.size());

    if (buffer.size() >= buffer_size_max) Flush();
    return result;
}

string VLog::ReadRecord(uint64_t address, uint32_t size) {
    if (address >= vlog_size) return string(buffer.c_str() + address - vlog_size, size);

    if (address + size > vlog_size) {
      printf("yue jie le \n");
}

    char* scratch = new char[size];
    Slice value;
/*
    printf("ReadRecord address: %lu, size: %u\n", address, size);
    printf("vlog_size: %lu\n", vlog_size);
    printf("buffer size: %lu\n", buffer.size());*/
    reader->Read(address, size, &value, scratch);
    /*printf("value: %d\n", *(uint8_t *)(value.data()));
    printf("scratch: %d\n", *(uint8_t*)scratch);*/
   //  printf("-------------ss-------\n");
    string result(value.data(), value.size());
    delete[] scratch;
    return result;
}

uint64_t VLog::getvlog_size(){
    return vlog_size;
}

int VLog::getvlog_buffer() {
    return buffer.size();
}

void VLog::Flush() {
    if (buffer.empty()) return;

    vlog_size += buffer.size();
    writer->Append(buffer);
    writer->Flush();
    buffer.clear();
    buffer.reserve(buffer_size_max * 2);
}

void VLog::Sync() {
    Flush();
    writer->Sync();
}

VLog::~VLog() {
    Flush();
}































}
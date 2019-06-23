/********************************
 File name: imgmgr/img.h
 Version:  0.1
 Description: Image 
*********************************/

#ifndef SRC_SUBMITTER_Image_H
#define SRC_SUBMITTER_Image_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "include/proxy.h"
#include "common/clynn/singleton.h"
//#include "common/clynn/rwlock.h"
//#include "common/clynn/rpc.h"

class Image{
public:
     bool CreateImage(const string& xml_path);
     //bool DeleteImage(const int32_t image_id);
     //bool QueryImage(const int32_t image_id);
     //bool QueryImageList();

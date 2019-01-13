
#######################################
# 
# FileName: script/setup_hdfs.sh
#  
#  
# Version:  0.1
# Description: CP .h .so TO default path(/usr/local/include...)
# usage: ./setup_hdfs.sh JAVA_HOME HADOOP_DIR
#######################################

JAVA_HOME=$1 # /usr/lib/java/jdk1.7.0_40/ 
HADOOP_DIR=$2 # /home/wm/work/hadoop/hadoop-1.0.4/

# java .h
# cp ${JAVA_HOME}/include/* /usr/include/
# cp ${JAVA_HOME}/include/linux/* /usr/include/

# java .so
# cp ${JAVA_HOME}/jre/lib/amd64/server/libjvm.so /usr/local/lib/

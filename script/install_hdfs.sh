
#######################################
# 
# FileName: script/install_hdfs.sh
# 
# 
# Version:  0.1
# Description: CP .h .so TO default path(/usr/local/include and /usr/local/lib)
# usage: ./install_hdfs.sh
#######################################

# hdfs .h
cp -r ../third_party/hdfs/include /usr/local/include/hdfs

# hdfs .socp ../third_party/hdfs/lib64/libhdfs.* /usr/local/lib/

import ctypes
import os
import sys

account_name = b'txfdvhd009sl'
sas_token = b'?sv=2019-12-12&ss=b&srt=so&sp=rw&se=2099-12-18T22:59:59Z&st=2020-12-18T10:52:44Z&spr=https&sig=qpmaaxkPJFYuSn5ulX60iRoWuOdMWC4Ps4PY7RK8tUM%3D'
container_name = b'signal-logger'

def to_bytes(data):
    return bytes(str(data).encode("utf-8"))

if __name__ == '__main__':

    if len(sys.argv) != 3:
        print("usage: {} file-to-upload blob-name".format(os.path.basename(sys.argv[0])))
        sys.exit(-1)

    file_path, blob_name = sys.argv[1:]

    wrapper = ctypes.cdll.LoadLibrary('./libazure-storage-wrapper.so')
    wrapper.get_error_code.restype = ctypes.c_char_p
    wrapper.get_error_name.restype = ctypes.c_char_p
    wrapper.get_error_description.restype = ctypes.c_char_p

    # print("Uploading file \"{}\" into {}...".format(file_path, blob_name))
    # result = wrapper.upload_file(
    #     account_name,
    #     sas_token,
    #     container_name,
    #     to_bytes(blob_name),
    #     to_bytes(file_path))

    data = open(file_path, 'rb').read()
    print("Uploading {} bytes into {}...".format(len(data), blob_name))

    result = wrapper.upload_buffer(
        account_name,
        sas_token,
        container_name,
        to_bytes(blob_name),
        to_bytes(data),
        len(data))

    if result == 0:
        print("Upload completed!")
    else:
        print("Error code: {}".format(wrapper.get_error_code()))
        print("Error name: {}".format(wrapper.get_error_name()))
        print("Error description: {}".format(wrapper.get_error_description()))

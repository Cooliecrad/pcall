from typing import Optional
from os import name
from ctypes import *

class Client:
    """Client的简单包装：Python实现
    """
    
    def __init__(self, filename, bf_size = 128):
        """初始化pcall客户端，实际是对C++实现的pcall客户端的包装

        Args:
            filename (_type_): 使用的pcall客户端动态库
            bf_size (int, optional): 向下位机发送的中间数据的最大长度. Defaults to 128.
        """
        self.__bf_size = bf_size

        if name == 'nt':
            self.__lib = CDLL(filename, winmode=0)
        elif name == 'posix':
            pass

    def parse(self, code: str) -> Optional[bytearray]:
        """解析语句，如果解析失败，返回None
        """
        buffer = bytearray(self.__bf_size)
        ret = self.__lib.parse(code, buffer, self.__bf_size)
        return buffer if ret == 0 else None

    def help(self) -> str:
        """读取帮助文档
        """
        _size = self.__lib.generate_help()
        bf = create_string_buffer(bytes(), size = _size + 1)
        self.__lib.copy_help(bf)
        return bf.value.decode('utf-8')
    
if __name__ == "__main__":
    client = Client("build/libclient.dll")
    print(client.help())
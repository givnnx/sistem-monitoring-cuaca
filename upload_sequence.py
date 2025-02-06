Import("env")
import os

def upload_filesystem_image(*args, **kwargs):
    print("Uploading filesystem image...")
    # Menjalankan upload filesystem menggunakan target `uploadfs`
    env.Execute("platformio run --target uploadfs")

def upload_main_program(*args, **kwargs):
    print("Uploading main program...")
    # Menjalankan upload program utama menggunakan target `upload`
    env.Execute("platformio run --target upload")

def open_serial_monitor(*args, **kwargs):
    print("Opening serial monitor...")
    # Membuka serial monitor setelah upload selesai
    env.Execute("platformio device monitor")

# Menambahkan fungsi ke dalam urutan
env.AddPreAction("upload", upload_filesystem_image)  # Menjalankan upload filesystem image
env.AddPostAction("upload", upload_main_program)      # Menjalankan upload program utama setelah filesystem image
env.AddPostAction("upload", open_serial_monitor)      # Membuka serial monitor setelah semuanya selesai

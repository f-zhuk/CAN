from datetime import datetime
from turtle import left
import time
import serial
import serial.tools.list_ports
import tkinter as tk

#
#def port_search():
#    port_name = "none"
#    while port_name == "none":
#        for port in serial.tools.list_ports.comports():
#           if port.vid == 1240 and port.pid == 223:
#                port_name = port.name
#                return port_name
#        time.sleep(0.1)

#
window = tk.Tk()
window.title("CANCDC")
window.geometry('1000x600')
window.configure(background="white")
text = tk.StringVar()
text.set("No adapters presented")
greeting = tk.Label(window, bg="white", textvariable=text, font=("Montserrat Light", 20))
#greeting.place(relx = 0.5, rely = 0.5, anchor = 'center')

class CANFrame:
    def __init__(self, ID, DLC, DATA):
        self.__ID = ID
        self.__data_length = DLC
        self.__data = DATA

    def get_ID(self):
        return self.__ID

    def get_NODEID(self):
        return (self.__ID & 0x7F)

    def get_TYPE(self):
        return ((self.__ID >> 7) & 0x0F)

class Adapter:
    def __init__(self):
        self.__port = ''
        self.__is_plugged = False
        self.__buffer = list()

        self.__frame_state = 0
        self.__temp_frame_ID = 0
        self.__temp_frame_DLC = 0
        self.__temp_frame_DATA = list()
        self.__temp_frame_COMSTAT = 0
        self.__last_frame = None

        self.__adapter_frame = tk.Frame(window)#, bg="white")
        self.__adapter_label = tk.Label(self.__adapter_frame, bg="white", text="Adapter", anchor=tk.W, padx=20, font=("Arial Rounded MT Bold", 14))
        self.__port_papam_label = tk.Label(self.__adapter_frame, bg="white", text="Port", anchor=tk.W, padx=20) #font=("Arial Rounded MT Bold", 14))
        self.__port_text = tk.StringVar(self.__adapter_frame, "None")
        self.__port_label = tk.Label(self.__adapter_frame, bg="white", textvariable=self.__port_text, anchor=tk.W, padx=10)

        self.__adapter_frame.columnconfigure(0, minsize=150, weight=1)
        self.__adapter_frame.columnconfigure(1, minsize=150, weight=1)
        self.__adapter_label.grid(column=0, row=0, sticky=tk.EW, padx=5, pady=5) 
        self.__port_papam_label.grid(column=0, row=1, sticky=tk.EW, padx=5, pady=5)       
        self.__port_label.grid(column=1, row=1, sticky=tk.EW, padx=5, pady=5)
        
    def is_plugged(self):
        if self.__port == '':
            while self.__port == '':
                for port in serial.tools.list_ports.comports():
                    if port.vid == 1240 and port.pid == 223:
                        self.__port = port
                        #self.__port_name = port.name
                window.update()
                time.sleep(0.1)
            self.ser = serial.Serial(self.__port.name, 230400, timeout=0, )
            self.ser.close()
            self.ser.open()

        if self.__port in serial.tools.list_ports.comports():
            self.__port_text.set(self.__port.name)
            self.__is_plugged = True
        else:
            self.__is_plugged = False
            self.ser.close()
        return self.__is_plugged

    def process(self):
        try:
            self.__buffer.extend(self.ser.read(10000))
        except serial.SerialTimeoutException:
            pass
        except:
            self.__port = ''
            self.is_plugged()
            return None           
        if self.__frame_state == 0 :
            while len(self.__buffer) > 0 and self.__buffer[0] != 0x55:
                self.__buffer.pop(0)     
            if len(self.__buffer) > 1 and self.__buffer[0] == 0x55 and self.__buffer[1] == 0xAA:
                self.__buffer.pop(0)
                self.__buffer.pop(0)

                #Reset temp frame
                self.__temp_frame_ID = 0
                self.__temp_frame_DLC = 0
                self.__temp_frame_DATA.clear()
                self.__temp_frame_COMSTAT = 0
                self.__last_frame = None

                self.__frame_state = 1
        if self.__frame_state == 1 :
            if len(self.__buffer) > 1 :
                self.__temp_frame_ID = self.__buffer.pop(0)
                self.__temp_frame_ID = (self.__temp_frame_ID<<8) | (self.__buffer.pop(0))
                self.__frame_state = 2
        if self.__frame_state == 2 :
            if len(self.__buffer) > 0 :
                self.__temp_frame_DLC = self.__buffer.pop(0)
                self.__frame_state = 3
        if self.__frame_state == 3 :
            if len(self.__buffer) >= self.__temp_frame_DLC :
                for x in range(self.__temp_frame_DLC) :
                    self.__temp_frame_DATA.append(self.__buffer.pop(0))
                self.__frame_state = 4
        if self.__frame_state == 4 :
            if len(self.__buffer) > 0 :
                self.__temp_frame_COMSTAT = self.__buffer.pop(0)
                self.__frame_state = 0 
                self.__last_frame = CANFrame(self.__temp_frame_ID,self.__temp_frame_DLC,self.__temp_frame_DATA)
                return self.__last_frame
        return None           

    def show_frame(self):
        self.__adapter_frame.pack(fill=tk.X)
        #self.__adapter_frame.pack_propagate(False) 
        #self.__port_label.pack(side = tk.LEFT)
        #self.__port_papam_label.pack(side = tk.RIGHT)

    def hide_frame(self):
        self.__adapter_frame.pack_forget()

class Device:
    def __init__(self, address):
        self.__can_address = address
        self.__dev_name = "Device " + str(self.__can_address)

        
        #devices = {}        #dict
        #self.__param_codes = list()
        #self.__param_types = list()
        self.__param_name_texts = {}    #dict
        self.__param_name_labels = {}   #dict
        self.__param_value_texts = {}   #dict
        self.__param_value_labels = {}  #dict

        self.__device_frame = tk.Frame(window)#, bg="white")
        self.__device_label = tk.Label(self.__device_frame, bg="white", text=self.__dev_name, anchor=tk.W, padx=20, font=("Arial Rounded MT Bold", 14))
        
        #self.__port_papam_label = tk.Label(self.__device_frame, bg="white", text="Port", anchor=tk.W, padx=20) #font=("Arial Rounded MT Bold", 14))
        #self.__port_text = tk.StringVar(self.__device_frame, "None")
        #self.__port_label = tk.Label(self.__device_frame, bg="white", textvariable=self.__port_text, anchor=tk.W, padx=10)

        self.__device_frame.columnconfigure(0, minsize=150, weight=1)
        self.__device_frame.columnconfigure(1, minsize=150, weight=1)
        self.__device_label.grid(column=0, row=0, sticky=tk.EW, padx=5, pady=5) 

        #self.__port_papam_label.grid(column=0, sticky=tk.EW, padx=5, pady=5)       
        #self.__port_label.grid(column=1, sticky=tk.EW, padx=5, pady=5)
        
    def process(self, frame):
        if self.__param_name_texts.get(frame.get_TYPE()) is None:
            self.__param_name_texts[frame.get_TYPE()] = tk.StringVar(self.__device_frame, "Name")
        if self.__param_name_labels.get(frame.get_TYPE()) is None:
            self.__param_name_labels[frame.get_TYPE()] = tk.Label(self.__device_frame, bg="white", textvariable=self.__param_name_texts[frame.get_TYPE()], anchor=tk.W, padx=10)
            self.__param_name_labels[frame.get_TYPE()].grid(column=0, row=frame.get_TYPE()+1, sticky=tk.EW, padx=5, pady=5)

        if self.__param_value_texts.get(frame.get_TYPE()) is None:
            self.__param_value_texts[frame.get_TYPE()] = tk.StringVar(self.__device_frame, "Value")
        if self.__param_value_labels.get(frame.get_TYPE()) is None:
            self.__param_value_labels[frame.get_TYPE()] = tk.Label(self.__device_frame, bg="white", textvariable=self.__param_value_texts[frame.get_TYPE()], anchor=tk.W, padx=10)       
            self.__param_value_labels[frame.get_TYPE()].grid(column=1, row=frame.get_TYPE()+1, sticky=tk.EW, padx=5, pady=5)
            

        match frame.get_TYPE():
            case 0x00:
                print("NMT node control")
            case 0x01:
                print("Emergency")
                self.__param_name_texts[frame.get_TYPE()].set("Emergency")
                self.__param_value_texts[frame.get_TYPE()].set("?")
            case 0x02:
                print("TimeStamp")
            case 0x03:
                print("PDO1 Transmit")
                self.__param_name_texts[frame.get_TYPE()].set("PDO1 Transmited")
            case 0x04:
                print("PDO1 Receive")
                self.__param_name_texts[frame.get_TYPE()].set("PDO1 Received")
            case 0x05:
                print("PDO2 Transmit")
            case 0x06:
                print("PDO2 Receive")
            case 0x07:
                print("PDO3 Transmit")
            case 0x08:
                print("PDO3 Receive")
            case 0x09:
                print("PDO4 Transmit")
            case 0x0A:
                print("PDO4 Receive")
            case 0x0B:
                print("SDO Transmit")
            case 0x0C:
                print("SDO Receive")
            case 0x0E:
                print("NMT Transmit")
                self.__param_name_texts[frame.get_TYPE()].set("NMT Transmit")
                self.__param_value_texts[frame.get_TYPE()].set("Last at "+datetime.now().strftime("%H:%M:%S.%f")[:-3])
            case _:
                print("Code not found")
        
    def show_frame(self):
        self.__device_frame.pack(fill=tk.X)

    def hide_frame(self):
        self.__param_name_texts.clear()
        for name_label in self.__param_name_labels:
            self.__param_name_labels[name_label].grid_remove()
        self.__param_name_labels.clear()
        
        self.__param_value_texts.clear()
        for value_label in self.__param_value_labels:
            self.__param_value_labels[value_label].grid_remove()
        self.__param_value_labels.clear()

        self.__device_frame.pack_forget()

#button.pack()
greeting.pack()
window.update()

adapter = Adapter()
devices = {}        #dict
new_frame = None
while True:
    #print
    if adapter.is_plugged(): 
        greeting.pack_forget()
        adapter.show_frame()
        #adapter.get_frame()
        new_frame = adapter.process()
        if new_frame is not None:
            if devices.get(new_frame.get_NODEID()) is None:
                devices[new_frame.get_NODEID()] = Device(new_frame.get_NODEID())
                devices[new_frame.get_NODEID()].show_frame()
            devices[new_frame.get_NODEID()].process(new_frame)
        new_frame = None
        
    else:
        adapter.hide_frame()
        for device in devices:
            devices[device].hide_frame()
        devices.clear()
        greeting.pack()
    #ser = serial.Serial('/dev/ttyUSB0')
    window.update()
    time.sleep(0.1)

#window.mainloop() 

import cv2
import serial

arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1) # adapt to your Arduino port

# Get user supplied values
cascPath = "haarcascade_frontalface_default.xml"

# Create the haar cascade
faceCascade = cv2.CascadeClassifier(cascPath)

# Read the video
video_capture = cv2.VideoCapture(0)


while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces in the image
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(100, 100),
        flags=cv2.CASCADE_SCALE_IMAGE
    )

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        x_center_frame = int(320 - (w / 2))
        y_center_frame = int(240 - (h / 2))

        threshold = h / 3

        # conditions
        # point (x,y)=(0,0) is in the upper left corner of video frame
        x_centered = x_center_frame - threshold <= x <= x_center_frame + threshold
        x_too_left = x < x_center_frame - threshold
        x_too_right = x > x_center_frame + threshold
        y_centered = y_center_frame - threshold <= y <= y_center_frame + threshold
        y_too_up = y < y_center_frame - threshold
        y_too_down = y > y_center_frame + threshold

        # we encode the video frame for communication between the Python and Arduino code as follows:
        # we define the required movements based on the robot starting from position (0,0)
        # _____________________________
        # | (-1,-1) | (0,-1) | (1,-1) |
        # -----------------------------
        # |  (-1,0) |  (0,0) |  (1,0) |
        # -----------------------------
        # |  (-1,1) |  (0,1) |  (1,1) |
        # -----------------------------
        if x_too_left and y_too_up:
            # person is in position (-1,-1) --> robot needs to move left and up
            arduino.write(bytes("(-1,-1)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_centered and y_too_up:
            # person is in position (0,-1) --> robot needs to move up
            arduino.write(bytes("(0,-1)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_too_right and y_too_up:
            # person is in position (1,-1) --> robot needs to move right and up
            arduino.write(bytes("(1,-1)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_too_left and y_centered:
            # person is in position (-1,0) --> robot needs to move left
            arduino.write(bytes("(-1,0)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_centered and y_centered:
            # person is in position (0,0) --> robot does not need to move
            arduino.write(bytes("(0,0)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        elif x_too_right and y_centered:
            # person is in position (1,0) --> robot needs to move right
            arduino.write(bytes("(1,0)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_too_left and y_too_down:
            # person is in position (-1,1) --> robot needs to move left and down
            arduino.write(bytes("(-1,1)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_centered and y_too_down:
            # person is in position (0,1) --> robot needs to move down
            arduino.write(bytes("(0,1)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        elif x_too_right and y_too_down:
            # person is in position (1,1) --> robot needs to move right and down
            arduino.write(bytes("(1,1)", 'utf-8'))
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        
        print(arduino.readline())

        cv2.putText(frame, f"x_center: {x_center_frame}, x: {x}, y_center: {y_center_frame}, y: {y}",
                    (10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

    cv2.imshow("Video", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()

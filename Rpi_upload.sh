# ! /bin/bash 

function takeshot() {
 if [ ! -f $jpegname ]
      then
         echo $jpegname  
         filename=$jpegname 
         sudo fswebcam -d /dev/video1 -r 1280x720 --bottom-banner --title "RaspberryPi C270 @sndnvaps" /home/pi/$filename
       else 
          echo "file $jpegname is exists!"
 fi 
 
 }
 
 function UploadToBitbucket() {

 if [  ! -d /opt/takeshot_rpi ]
        then 
            mkdir -p /opt/takeshot_rpi  
            cd /opt/takeshot_rpi 
            git init 
            git remote add origin git@bitbucket.org:sndnvaps/rpi_upload_pic.git
         else 
            filename=$jpegname
            echo $filename
            cp /home/pi/$filename /opt/takeshot_rpi/ 
            cd /opt/takeshot_rpi 
            git add * 
            git commit -s -m "update $jpegname"
            git push origin master:master 
            echo "upload $jpegname to bitbucket.org done."
 fi 
 
} 


random=$(date +%s%N)
jpegname=$random.jpg

takeshot
UploadToBitbucket




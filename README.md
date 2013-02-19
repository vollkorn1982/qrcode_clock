# Photo Time Correction

Using QR codes to semi-automatically correct EXIF time stamps of photos.

## The QR code clock

A clock showing the seconds since 01.01.1970 00:00 UTC as a QR code.

## Problem

Every camera has an internal clock to set the EXIF timestamp when the photo was
taken. Often users don't take care of accurately setting these internal clocks,
which leads to problems with use cases relying on the EXIF timestamp.

Two scenarios come to mind at once:

1. **Merging photo collections of multiple users.** When the camera's clocks are
set at different times it can be quite a hassle to properly sort all photos by
their true chronological sequence.

2. **Geotagging pictures.** Geotagging with external tracking devices relies on
the EXIF timestamp of the photos. If this timestamp is off by only a few seconds
this can result in huge position errors.

## Idea

Although the camera's clocks often aren't set properly they're running stable
and all photos imported from one camera have the same offset. To figure out what
this offset is it's enough to find one photo you know which time it was really
taken at. The manual way would be to find a photo of an accurate clock like from
a church tower, calculate the difference of that time to this photo's EXIF time
stamp and correct all photos by that camera by this difference.

Now we take a photo of a computer screen — thanks to NTP — accurately showing 
the current time in a machine readable way as a QR code. When importing the
photos they are searched for a QR code and if one is found all photos are
corrected by the calculated offset as described above.

# Project plan

The aim of this project is to create a stand alone application as a proof of
concept.

Two features are needed:

1. Showing a QR code with the current time

2. Reading QR codes in a folder of photos and correct the EXIF timestamps.

This is done writing C++ code and using Qt because the author is familiar with
these.

# Requirements

qt4-dev-tools >=4.8.1
qt4-qmake >=4.8.1
libexiv2-dev >= 0.23
libqrencode-dev >= 3.3.0
libdecodeqr-dev >= 0.9.3

## Recommended

I recommend to install Qt-Creator with all its dependencies to comfortably
work with the source code.

# Installation

Navigate to the directory where you placed the files and do

  # ./qmake
  # ./make

to compile the project and 

  # ./qrcode_clock

to start the clock.


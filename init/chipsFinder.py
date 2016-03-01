#!/usr/lib/python3.4
import os


#recupere le nom des repertoires dans le dossier courant
chip_ehrpwm = os.listdir('/sys/devices/platform/ocp/subsystem/devices/48302200.ehrpwm/pwm')
chip_ecap = os.listdir('/sys/devices/platform/ocp/subsystem/devices/48300100.ecap/pwm/')

with open('pwmcfg/ehrpwm.cfg', 'w') as file:
	file.write(chip_ehrpwm[0])


with open('pwmcfg/ecap.cfg', 'w') as file:
	file.write(chip_ecap[0])

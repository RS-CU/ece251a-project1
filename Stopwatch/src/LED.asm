$NOMOD51
Name LED
;-----------------------------------------------------------------------------
; SB3_blinky.ASM
;-----------------------------------------------------------------------------
;  TARGET MCU  :  EFM8SB1
;  DESCRIPTION :  This program illustrates how to disable the watchdog timer,
;                 configure the Crossbar, configure a port and write to a port
;                 I/O pin.
;
; 	NOTES:
;
;-----------------------------------------------------------------------------

$include (SI_EFM8BB3_Defs.inc)            ; Include register definition file.
PUBLIC LED
;-----------------------------------------------------------------------------
; EQUATES
;-----------------------------------------------------------------------------

GREEN_LED   equ   P1.4
BLUE_LED   equ   P1.5
RED_LED   equ   P1.6                    ; Green LED: '1' is ON
DISP_EN   equ   P2.7                    ; Display Enable:
                                           ;   '0' is Board Contoller driven
                                           ;   '1' is EFM8 driven
;-----------------------------------------------------------------------------
; RESET and INTERRUPT VECTORS
;-----------------------------------------------------------------------------

            ; Reset Vector
 ;           cseg AT 0
   ;         ljmp LED                     ; Locate a jump to the start of
                                          ; code at the reset vector.

;-----------------------------------------------------------------------------
; CODE SEGMENT
;-----------------------------------------------------------------------------


Blink       segment  CODE

            rseg  Blink                ; Switch to this code segment.
            using    0                    ; Specify register bank for the
                                          ; following program code.

LED:
            ; Disable the WDT.
            anl   PCA0MD, #NOT(040h)      ; clear Watchdog Enable bit

            ; Enable the Port I/O Crossbar
            orl   P1SKIP, #02h            ; skip LED pin in crossbar
                                          ; assignments
            mov   XBR2, #40h
            orl   P1MDOUT, #02h           ; make LED pin output push-pull
            orl   P2MDOUT, #80h           ; make DISP_EN pin output push-pull

            ; Initialize LED to OFF
            setb   GREEN_LED
            setb BLUE_LED
            setb RED_LED
            ; Set Display Enable pin to Board Controller driven
            clr   DISP_EN

            ; Simple delay loop.

            mov   R4, #04h				; Every 2 gives the number of cycles within loop
Loop2:      mov   R7, #15h				; Controls period of cycle
Loop1:      mov   R6, #00h
Loop0:      mov   R5, #00h
            djnz  R5, $
            djnz  R6, Loop0
            djnz  R7, Loop1
            cpl   RED_LED               ; Toggle LED
            djnz  R4, Loop2
            setb   RED_LED

            mov   R4, #02h				; Every 2 gives the number of cycles within loop
Loop5:      mov   R7, #15h				; Controls period of cycle
Loop4:      mov   R6, #00h
Loop3:      mov   R5, #00h
            djnz  R5, $
            djnz  R6, Loop3
            djnz  R7, Loop4
            cpl   RED_LED               ; Toggle LED
            cpl   GREEN_LED
            djnz  R4, Loop5
            setb   RED_LED
            setb   GREEN_LED

            mov   R4, #02h				; Every 2 gives the number of cycles within loop
Loop8:      mov   R7, #15h				; Controls period of cycle
Loop7:      mov   R6, #00h
Loop6:      mov   R5, #00h
            djnz  R5, $
            djnz  R6, Loop6
            djnz  R7, Loop7
            cpl   GREEN_LED              ; Toggle LED
            djnz  R4, Loop8
            setb   GREEN_LED
			RET


;HERE:       sjmp HERE
;-----------------------------------------------------------------------------
; End of file.
END

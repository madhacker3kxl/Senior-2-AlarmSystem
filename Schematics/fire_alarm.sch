<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.1.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Atmel_By_element14_Batch_1-00">
<description>Developed by element14 :&lt;br&gt;
element14 CAD Library consolidation.ulp
at 27/07/2012 14:02:49</description>
<packages>
<package name="DIP254P762X533-8">
<pad name="1" x="-7.62" y="7.62" drill="1.1176" shape="square"/>
<pad name="2" x="-7.62" y="5.08" drill="1.1176"/>
<pad name="3" x="-7.62" y="2.54" drill="1.1176"/>
<pad name="4" x="-7.62" y="0" drill="1.1176"/>
<pad name="5" x="0" y="0" drill="1.1176"/>
<pad name="6" x="0" y="2.54" drill="1.1176"/>
<pad name="7" x="0" y="5.08" drill="1.1176"/>
<pad name="8" x="0" y="7.62" drill="1.1176"/>
<wire x1="-7.2898" y1="-1.27" x2="-0.3302" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.3302" y1="8.89" x2="-3.5052" y2="8.89" width="0.1524" layer="21"/>
<wire x1="-3.5052" y1="8.89" x2="-4.1148" y2="8.89" width="0.1524" layer="21"/>
<wire x1="-4.1148" y1="8.89" x2="-6.477" y2="8.89" width="0.1524" layer="21"/>
<wire x1="-3.5052" y1="8.89" x2="-4.1148" y2="8.89" width="0.1524" layer="21" curve="-180"/>
<text x="-8.2042" y="8.7376" size="1.27" layer="21" ratio="6" rot="SR0">*</text>
<wire x1="-7.366" y1="7.0612" x2="-7.366" y2="8.1788" width="0" layer="51"/>
<wire x1="-7.366" y1="8.1788" x2="-8.1788" y2="8.1788" width="0" layer="51"/>
<wire x1="-8.1788" y1="8.1788" x2="-8.1788" y2="7.0612" width="0" layer="51"/>
<wire x1="-8.1788" y1="7.0612" x2="-7.366" y2="7.0612" width="0" layer="51"/>
<wire x1="-7.366" y1="4.5212" x2="-7.366" y2="5.6388" width="0" layer="51"/>
<wire x1="-7.366" y1="5.6388" x2="-8.1788" y2="5.6388" width="0" layer="51"/>
<wire x1="-8.1788" y1="5.6388" x2="-8.1788" y2="4.5212" width="0" layer="51"/>
<wire x1="-8.1788" y1="4.5212" x2="-7.366" y2="4.5212" width="0" layer="51"/>
<wire x1="-7.366" y1="1.9812" x2="-7.366" y2="3.0988" width="0" layer="51"/>
<wire x1="-7.366" y1="3.0988" x2="-8.1788" y2="3.0988" width="0" layer="51"/>
<wire x1="-8.1788" y1="3.0988" x2="-8.1788" y2="1.9812" width="0" layer="51"/>
<wire x1="-8.1788" y1="1.9812" x2="-7.366" y2="1.9812" width="0" layer="51"/>
<wire x1="-7.366" y1="-0.5588" x2="-7.366" y2="0.5588" width="0" layer="51"/>
<wire x1="-7.366" y1="0.5588" x2="-8.1788" y2="0.5588" width="0" layer="51"/>
<wire x1="-8.1788" y1="0.5588" x2="-8.1788" y2="-0.5588" width="0" layer="51"/>
<wire x1="-8.1788" y1="-0.5588" x2="-7.366" y2="-0.5588" width="0" layer="51"/>
<wire x1="-0.254" y1="0.5588" x2="-0.254" y2="-0.5588" width="0" layer="51"/>
<wire x1="-0.254" y1="-0.5588" x2="0.5588" y2="-0.5588" width="0" layer="51"/>
<wire x1="0.5588" y1="-0.5588" x2="0.5588" y2="0.5588" width="0" layer="51"/>
<wire x1="0.5588" y1="0.5588" x2="-0.254" y2="0.5588" width="0" layer="51"/>
<wire x1="-0.254" y1="3.0988" x2="-0.254" y2="1.9812" width="0" layer="51"/>
<wire x1="-0.254" y1="1.9812" x2="0.5588" y2="1.9812" width="0" layer="51"/>
<wire x1="0.5588" y1="1.9812" x2="0.5588" y2="3.0988" width="0" layer="51"/>
<wire x1="0.5588" y1="3.0988" x2="-0.254" y2="3.0988" width="0" layer="51"/>
<wire x1="-0.254" y1="5.6388" x2="-0.254" y2="4.5212" width="0" layer="51"/>
<wire x1="-0.254" y1="4.5212" x2="0.5588" y2="4.5212" width="0" layer="51"/>
<wire x1="0.5588" y1="4.5212" x2="0.5588" y2="5.6388" width="0" layer="51"/>
<wire x1="0.5588" y1="5.6388" x2="-0.254" y2="5.6388" width="0" layer="51"/>
<wire x1="-0.254" y1="8.1788" x2="-0.254" y2="7.0612" width="0" layer="51"/>
<wire x1="-0.254" y1="7.0612" x2="0.5588" y2="7.0612" width="0" layer="51"/>
<wire x1="0.5588" y1="7.0612" x2="0.5588" y2="8.1788" width="0" layer="51"/>
<wire x1="0.5588" y1="8.1788" x2="-0.254" y2="8.1788" width="0" layer="51"/>
<wire x1="-7.366" y1="-1.27" x2="-0.254" y2="-1.27" width="0" layer="51"/>
<wire x1="-0.254" y1="-1.27" x2="-0.254" y2="8.89" width="0" layer="51"/>
<wire x1="-0.254" y1="8.89" x2="-3.5052" y2="8.89" width="0" layer="51"/>
<wire x1="-3.5052" y1="8.89" x2="-4.1148" y2="8.89" width="0" layer="51"/>
<wire x1="-4.1148" y1="8.89" x2="-7.366" y2="8.89" width="0" layer="51"/>
<wire x1="-7.366" y1="8.89" x2="-7.366" y2="-1.27" width="0" layer="51"/>
<wire x1="-3.5052" y1="8.89" x2="-4.1148" y2="8.89" width="0" layer="51" curve="-180"/>
<text x="-8.2042" y="8.7376" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<text x="-8.5598" y="-4.1656" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-7.2644" y="10.795" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="ATTINY85-20PU">
<pin name="VCC" x="-83.82" y="5.08" length="middle" direction="pwr"/>
<pin name="(PCINT3/XTAL1/CLKI/~OC1B/ADC3)_PB3" x="-83.82" y="0" length="middle"/>
<pin name="(PCINT4/XTAL2/CLKO/OC1B/ADC2)_PB4" x="-83.82" y="-2.54" length="middle"/>
<pin name="(PCINT5/~RESET/ADC0/DW)_PB5" x="-83.82" y="-5.08" length="middle"/>
<pin name="GND" x="-83.82" y="-10.16" length="middle" direction="pas"/>
<pin name="PB0_(MOSI/DI/SDA/AIN0/OC0A/~OC1A/AREF/PCINT0)" x="83.82" y="5.08" length="middle" rot="R180"/>
<pin name="PB1_(MISO/DO/AIN1/OC0B/OC1A/PCINT1)" x="83.82" y="2.54" length="middle" rot="R180"/>
<pin name="PB2_(SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)" x="83.82" y="0" length="middle" rot="R180"/>
<wire x1="-78.74" y1="10.16" x2="-78.74" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="-78.74" y1="-15.24" x2="78.74" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="78.74" y1="-15.24" x2="78.74" y2="10.16" width="0.4064" layer="94"/>
<wire x1="78.74" y1="10.16" x2="-78.74" y2="10.16" width="0.4064" layer="94"/>
<text x="-5.6388" y="11.7602" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-5.0038" y="-18.415" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ATTINY85-20PU" prefix="U">
<description>8-bit Microcontroller with In-System Programmable Flash</description>
<gates>
<gate name="A" symbol="ATTINY85-20PU" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DIP254P762X533-8">
<connects>
<connect gate="A" pin="(PCINT3/XTAL1/CLKI/~OC1B/ADC3)_PB3" pad="2"/>
<connect gate="A" pin="(PCINT4/XTAL2/CLKO/OC1B/ADC2)_PB4" pad="3"/>
<connect gate="A" pin="(PCINT5/~RESET/ADC0/DW)_PB5" pad="1"/>
<connect gate="A" pin="GND" pad="4"/>
<connect gate="A" pin="PB0_(MOSI/DI/SDA/AIN0/OC0A/~OC1A/AREF/PCINT0)" pad="5"/>
<connect gate="A" pin="PB1_(MISO/DO/AIN1/OC0B/OC1A/PCINT1)" pad="6"/>
<connect gate="A" pin="PB2_(SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)" pad="7"/>
<connect gate="A" pin="VCC" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MPN" value="ATTINY85-20PU" constant="no"/>
<attribute name="OC_FARNELL" value="1455162" constant="no"/>
<attribute name="OC_NEWARK" value="58M3796" constant="no"/>
<attribute name="PACKAGE" value="PDIP-8" constant="no"/>
<attribute name="SUPPLIER" value="Atmel" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U1" library="Atmel_By_element14_Batch_1-00" deviceset="ATTINY85-20PU" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="A" x="119.38" y="-220.98"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>

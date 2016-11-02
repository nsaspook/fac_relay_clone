<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.7.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
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
<library name="microchip_bluetooth_v101">
<packages>
<package name="RN4020SMD">
<smd name="P10" x="2.75" y="0.25" dx="1.5" dy="0.8" layer="1" rot="R90"/>
<smd name="P11" x="3.95" y="0.25" dx="1.5" dy="0.8" layer="1" rot="R90"/>
<smd name="P12" x="5.15" y="0.25" dx="1.5" dy="0.8" layer="1" rot="R90"/>
<smd name="P13" x="6.35" y="0.25" dx="1.5" dy="0.8" layer="1" rot="R90"/>
<smd name="P14" x="7.55" y="0.25" dx="1.5" dy="0.8" layer="1" rot="R90"/>
<smd name="P15" x="8.75" y="0.25" dx="1.5" dy="0.8" layer="1" rot="R90"/>
<wire x1="0" y1="0" x2="11.5" y2="0" width="0.127" layer="21"/>
<smd name="P08" x="0.25" y="2.5" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P07" x="0.25" y="3.7" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P06" x="0.25" y="4.9" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P05" x="0.25" y="6.1" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P04" x="0.25" y="7.3" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P03" x="0.25" y="8.5" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P02" x="0.25" y="9.7" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P01" x="0.25" y="10.9" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P17" x="11.25" y="2.5" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P18" x="11.25" y="3.7" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P19" x="11.25" y="4.9" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P20" x="11.25" y="6.1" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P21" x="11.25" y="7.3" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P22" x="11.25" y="8.5" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P23" x="11.25" y="9.7" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<smd name="P24" x="11.25" y="10.9" dx="1.5" dy="0.8" layer="1" rot="R180"/>
<wire x1="0" y1="0" x2="0" y2="14.55" width="0.127" layer="21"/>
<wire x1="0" y1="14.55" x2="11.5" y2="14.55" width="0.127" layer="21"/>
<wire x1="11.5" y1="14.55" x2="11.5" y2="0" width="0.127" layer="21"/>
<wire x1="0" y1="14.55" x2="0" y2="19.5" width="0.127" layer="21"/>
<wire x1="0" y1="19.5" x2="11.5" y2="19.5" width="0.127" layer="21"/>
<wire x1="11.5" y1="19.5" x2="11.5" y2="14.55" width="0.127" layer="21"/>
<wire x1="0.25" y1="0.35" x2="11.25" y2="0.35" width="0.127" layer="21"/>
<wire x1="11.25" y1="0.35" x2="11.25" y2="14.2" width="0.127" layer="21"/>
<wire x1="11.25" y1="14.2" x2="0.25" y2="14.2" width="0.127" layer="21"/>
<wire x1="0.25" y1="14.2" x2="0.25" y2="0.35" width="0.127" layer="21"/>
<text x="2" y="5.1" size="1.27" layer="21">Microchip
RN4020</text>
<rectangle x1="2.7" y1="14.55" x2="3.2" y2="19.1" layer="21"/>
<rectangle x1="0.4" y1="18.6" x2="2.7" y2="19.1" layer="21"/>
<rectangle x1="0.4" y1="15.2" x2="1.2" y2="18.6" layer="21"/>
<rectangle x1="3.2" y1="18.6" x2="4.8" y2="19.1" layer="21"/>
<rectangle x1="4.3" y1="16.6" x2="4.8" y2="18.6" layer="21"/>
<rectangle x1="4.8" y1="16.6" x2="6.4" y2="17.1" layer="21"/>
<rectangle x1="5.9" y1="17.1" x2="6.4" y2="19.1" layer="21"/>
<rectangle x1="6.4" y1="18.6" x2="8" y2="19.1" layer="21"/>
<rectangle x1="7.5" y1="16.6" x2="8" y2="18.6" layer="21"/>
<rectangle x1="8" y1="16.6" x2="9.6" y2="17.1" layer="21"/>
<rectangle x1="9.1" y1="17.1" x2="9.6" y2="19.1" layer="21"/>
<rectangle x1="9.6" y1="18.6" x2="11.2" y2="19.1" layer="21"/>
<rectangle x1="10.7" y1="15.75" x2="11.2" y2="18.6" layer="21"/>
<rectangle x1="0" y1="0" x2="1.6" y2="1.8" layer="41"/>
<rectangle x1="9.9" y1="0" x2="11.5" y2="1.8" layer="41"/>
<rectangle x1="9.9" y1="12.75" x2="11.5" y2="14.55" layer="41"/>
<rectangle x1="0" y1="12.75" x2="1.6" y2="14.55" layer="41"/>
<rectangle x1="1.85" y1="12.95" x2="4.05" y2="14.55" layer="41"/>
<rectangle x1="1.85" y1="12.95" x2="4.05" y2="14.55" layer="42"/>
<rectangle x1="1.85" y1="12.95" x2="4.05" y2="14.55" layer="43"/>
<rectangle x1="0" y1="0" x2="11.5" y2="19.5" layer="39"/>
<rectangle x1="0" y1="14.55" x2="11.5" y2="19.5" layer="40"/>
</package>
</packages>
<symbols>
<symbol name="RN4020SCH">
<pin name="1-GND" x="-22.86" y="20.32" length="middle"/>
<pin name="2-AIO2" x="-22.86" y="17.78" length="middle"/>
<pin name="3-AIO1" x="-22.86" y="15.24" length="middle"/>
<pin name="4-AIO0" x="-22.86" y="12.7" length="middle"/>
<pin name="5-TX" x="-22.86" y="10.16" length="middle"/>
<pin name="6-RX" x="-22.86" y="7.62" length="middle"/>
<pin name="7-WAKESW" x="-22.86" y="5.08" length="middle"/>
<pin name="8-CMD-MLDP" x="-22.86" y="2.54" length="middle"/>
<pin name="10-PIO1-SCK" x="-7.62" y="-30.48" length="middle" rot="R90"/>
<pin name="11-MLDPEV-PIO2-CS" x="-5.08" y="-30.48" length="middle" rot="R90"/>
<pin name="12-WS-PIO3-MOSI" x="-2.54" y="-30.48" length="middle" rot="R90"/>
<pin name="13-PIO4-MISO" x="0" y="-30.48" length="middle" rot="R90"/>
<pin name="14-CTS-PIO5" x="2.54" y="-30.48" length="middle" rot="R90"/>
<pin name="15-WAKEHW" x="5.08" y="-30.48" length="middle" rot="R90"/>
<pin name="17-SPI-/PIO" x="20.32" y="2.54" length="middle" rot="R180"/>
<pin name="18-RTS-PIO6" x="20.32" y="5.08" length="middle" rot="R180"/>
<pin name="19-PIO7" x="20.32" y="7.62" length="middle" rot="R180"/>
<pin name="20-RSVD" x="20.32" y="10.16" length="middle" rot="R180"/>
<pin name="21-RSVD" x="20.32" y="12.7" length="middle" rot="R180"/>
<pin name="22-RSVD" x="20.32" y="15.24" length="middle" rot="R180"/>
<pin name="23-VDD" x="20.32" y="17.78" length="middle" rot="R180"/>
<pin name="24-GND" x="20.32" y="20.32" length="middle" rot="R180"/>
<text x="-5.08" y="17.78" size="1.27" layer="94">Microchip
RN4020</text>
<wire x1="-17.78" y1="-25.4" x2="-12.7" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-25.4" x2="10.16" y2="-25.4" width="0.254" layer="94"/>
<wire x1="10.16" y1="-25.4" x2="15.24" y2="-25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="-25.4" x2="15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="15.24" y2="22.86" width="0.254" layer="94"/>
<wire x1="15.24" y1="22.86" x2="-17.78" y2="22.86" width="0.254" layer="94"/>
<wire x1="-17.78" y1="22.86" x2="-17.78" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-20.32" x2="-17.78" y2="-25.4" width="0.254" layer="94"/>
<wire x1="-17.78" y1="22.86" x2="-17.78" y2="33.02" width="0.254" layer="94"/>
<wire x1="-17.78" y1="33.02" x2="15.24" y2="33.02" width="0.254" layer="94"/>
<wire x1="15.24" y1="33.02" x2="15.24" y2="22.86" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-20.32" x2="-12.7" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-20.32" x2="-12.7" y2="-25.4" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="10.16" y2="-20.32" width="0.254" layer="94"/>
<wire x1="10.16" y1="-20.32" x2="10.16" y2="-25.4" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="RN4020">
<gates>
<gate name="G$1" symbol="RN4020SCH" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RN4020SMD">
<connects>
<connect gate="G$1" pin="1-GND" pad="P01"/>
<connect gate="G$1" pin="10-PIO1-SCK" pad="P10"/>
<connect gate="G$1" pin="11-MLDPEV-PIO2-CS" pad="P11"/>
<connect gate="G$1" pin="12-WS-PIO3-MOSI" pad="P12"/>
<connect gate="G$1" pin="13-PIO4-MISO" pad="P13"/>
<connect gate="G$1" pin="14-CTS-PIO5" pad="P14"/>
<connect gate="G$1" pin="15-WAKEHW" pad="P15"/>
<connect gate="G$1" pin="17-SPI-/PIO" pad="P17"/>
<connect gate="G$1" pin="18-RTS-PIO6" pad="P18"/>
<connect gate="G$1" pin="19-PIO7" pad="P19"/>
<connect gate="G$1" pin="2-AIO2" pad="P02"/>
<connect gate="G$1" pin="20-RSVD" pad="P20"/>
<connect gate="G$1" pin="21-RSVD" pad="P21"/>
<connect gate="G$1" pin="22-RSVD" pad="P22"/>
<connect gate="G$1" pin="23-VDD" pad="P23"/>
<connect gate="G$1" pin="24-GND" pad="P24"/>
<connect gate="G$1" pin="3-AIO1" pad="P03"/>
<connect gate="G$1" pin="4-AIO0" pad="P04"/>
<connect gate="G$1" pin="5-TX" pad="P05"/>
<connect gate="G$1" pin="6-RX" pad="P06"/>
<connect gate="G$1" pin="7-WAKESW" pad="P07"/>
<connect gate="G$1" pin="8-CMD-MLDP" pad="P08"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-lstb">
<description>&lt;b&gt;Pin Headers&lt;/b&gt;&lt;p&gt;
Naming:&lt;p&gt;
MA = male&lt;p&gt;
# contacts - # rows&lt;p&gt;
W = angled&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="MA08-1">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-9.525" y1="1.27" x2="-8.255" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="1.27" x2="-7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="-0.635" x2="-8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-7.62" y1="0.635" x2="-6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="1.27" x2="-5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-1.27" x2="-6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-6.985" y1="-1.27" x2="-7.62" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-9.525" y1="1.27" x2="-10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-0.635" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-8.255" y1="-1.27" x2="-9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="-1.27" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.715" y2="1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.985" y2="1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="6.985" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.985" y1="-1.27" x2="5.715" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="9.525" y2="1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="1.27" x2="10.16" y2="0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0.635" x2="10.16" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="10.16" y1="-0.635" x2="9.525" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="8.255" y1="1.27" x2="7.62" y2="0.635" width="0.1524" layer="21"/>
<wire x1="7.62" y1="-0.635" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="9.525" y1="-1.27" x2="8.255" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-10.16" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-9.398" y="-2.921" size="1.27" layer="21" ratio="10">1</text>
<text x="8.255" y="1.651" size="1.27" layer="21" ratio="10">8</text>
<text x="-1.27" y="-2.921" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-0.254" x2="-6.096" y2="0.254" layer="51"/>
<rectangle x1="-9.144" y1="-0.254" x2="-8.636" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="6.096" y1="-0.254" x2="6.604" y2="0.254" layer="51"/>
<rectangle x1="8.636" y1="-0.254" x2="9.144" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MA08-1">
<wire x1="3.81" y1="-10.16" x2="-1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="12.7" x2="-1.27" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-10.16" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="12.7" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<text x="-1.27" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<text x="-1.27" y="13.462" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MA08-1" prefix="SV" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="MA08-1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MA08-1">
<connects>
<connect gate="1" pin="1" pad="1"/>
<connect gate="1" pin="2" pad="2"/>
<connect gate="1" pin="3" pad="3"/>
<connect gate="1" pin="4" pad="4"/>
<connect gate="1" pin="5" pad="5"/>
<connect gate="1" pin="6" pad="6"/>
<connect gate="1" pin="7" pad="7"/>
<connect gate="1" pin="8" pad="8"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
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
<part name="U$1" library="microchip_bluetooth_v101" deviceset="RN4020" device=""/>
<part name="SV1" library="con-lstb" deviceset="MA08-1" device="" value="pins a"/>
<part name="SV2" library="con-lstb" deviceset="MA08-1" device="" value="pins b"/>
<part name="SUPPLY1" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY2" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY3" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY4" library="supply2" deviceset="GND" device=""/>
<part name="+3V1" library="supply1" deviceset="+3V3" device=""/>
<part name="+3V2" library="supply1" deviceset="+3V3" device=""/>
<part name="SV3" library="con-lstb" deviceset="MA08-1" device="" value="gpio"/>
<part name="SUPPLY5" library="supply2" deviceset="GND" device=""/>
<part name="+3V3" library="supply1" deviceset="+3V3" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="73.66" y="50.8"/>
<instance part="SV1" gate="1" x="12.7" y="38.1"/>
<instance part="SV2" gate="1" x="116.84" y="38.1"/>
<instance part="SUPPLY1" gate="GND" x="20.32" y="27.94"/>
<instance part="SUPPLY2" gate="GND" x="124.46" y="27.94"/>
<instance part="SUPPLY3" gate="GND" x="33.02" y="81.28"/>
<instance part="SUPPLY4" gate="GND" x="111.76" y="81.28"/>
<instance part="+3V1" gate="G$1" x="116.84" y="73.66"/>
<instance part="+3V2" gate="G$1" x="33.02" y="25.4" rot="R180"/>
<instance part="SV3" gate="1" x="25.4" y="2.54"/>
<instance part="SUPPLY5" gate="GND" x="35.56" y="-10.16"/>
<instance part="+3V3" gate="G$1" x="45.72" y="-7.62" rot="R270"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="SV1" gate="1" pin="1"/>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="SV2" gate="1" pin="1"/>
<pinref part="SUPPLY2" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="1-GND"/>
<wire x1="50.8" y1="71.12" x2="43.18" y2="71.12" width="0.1524" layer="91"/>
<wire x1="43.18" y1="71.12" x2="43.18" y2="83.82" width="0.1524" layer="91"/>
<pinref part="SUPPLY3" gate="GND" pin="GND"/>
<wire x1="43.18" y1="83.82" x2="33.02" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="24-GND"/>
<wire x1="93.98" y1="71.12" x2="104.14" y2="71.12" width="0.1524" layer="91"/>
<wire x1="104.14" y1="71.12" x2="104.14" y2="83.82" width="0.1524" layer="91"/>
<pinref part="SUPPLY4" gate="GND" pin="GND"/>
<wire x1="104.14" y1="83.82" x2="111.76" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SV3" gate="1" pin="1"/>
<wire x1="33.02" y1="-5.08" x2="35.56" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-5.08" x2="35.56" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="GND" pin="GND"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="23-VDD"/>
<wire x1="93.98" y1="68.58" x2="111.76" y2="68.58" width="0.1524" layer="91"/>
<wire x1="111.76" y1="68.58" x2="111.76" y2="71.12" width="0.1524" layer="91"/>
<wire x1="111.76" y1="71.12" x2="116.84" y2="71.12" width="0.1524" layer="91"/>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
</segment>
<segment>
<pinref part="SV1" gate="1" pin="2"/>
<wire x1="20.32" y1="33.02" x2="33.02" y2="33.02" width="0.1524" layer="91"/>
<wire x1="33.02" y1="33.02" x2="33.02" y2="27.94" width="0.1524" layer="91"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
</segment>
<segment>
<pinref part="SV3" gate="1" pin="2"/>
<wire x1="33.02" y1="-2.54" x2="38.1" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="38.1" y1="-2.54" x2="38.1" y2="-7.62" width="0.1524" layer="91"/>
<wire x1="38.1" y1="-7.62" x2="43.18" y2="-7.62" width="0.1524" layer="91"/>
<pinref part="+3V3" gate="G$1" pin="+3V3"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="SV2" gate="1" pin="8"/>
<wire x1="124.46" y1="48.26" x2="132.08" y2="48.26" width="0.1524" layer="91"/>
<wire x1="132.08" y1="48.26" x2="132.08" y2="88.9" width="0.1524" layer="91"/>
<wire x1="132.08" y1="88.9" x2="30.48" y2="88.9" width="0.1524" layer="91"/>
<wire x1="30.48" y1="88.9" x2="30.48" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="8-CMD-MLDP"/>
<wire x1="50.8" y1="53.34" x2="30.48" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="SV2" gate="1" pin="6"/>
<wire x1="124.46" y1="43.18" x2="134.62" y2="43.18" width="0.1524" layer="91"/>
<wire x1="134.62" y1="43.18" x2="134.62" y2="91.44" width="0.1524" layer="91"/>
<wire x1="134.62" y1="91.44" x2="27.94" y2="91.44" width="0.1524" layer="91"/>
<wire x1="27.94" y1="91.44" x2="27.94" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="5-TX"/>
<wire x1="27.94" y1="60.96" x2="50.8" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="SV2" gate="1" pin="5"/>
<wire x1="124.46" y1="40.64" x2="139.7" y2="40.64" width="0.1524" layer="91"/>
<wire x1="139.7" y1="40.64" x2="139.7" y2="93.98" width="0.1524" layer="91"/>
<wire x1="139.7" y1="93.98" x2="25.4" y2="93.98" width="0.1524" layer="91"/>
<wire x1="25.4" y1="93.98" x2="25.4" y2="58.42" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="6-RX"/>
<wire x1="50.8" y1="58.42" x2="25.4" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="SV2" gate="1" pin="4"/>
<wire x1="124.46" y1="38.1" x2="144.78" y2="38.1" width="0.1524" layer="91"/>
<wire x1="144.78" y1="38.1" x2="144.78" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="18-RTS-PIO6"/>
<wire x1="144.78" y1="55.88" x2="93.98" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="SV2" gate="1" pin="3"/>
<wire x1="124.46" y1="35.56" x2="139.7" y2="35.56" width="0.1524" layer="91"/>
<wire x1="139.7" y1="35.56" x2="139.7" y2="10.16" width="0.1524" layer="91"/>
<wire x1="139.7" y1="10.16" x2="76.2" y2="10.16" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="14-CTS-PIO5"/>
<wire x1="76.2" y1="10.16" x2="76.2" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="SV1" gate="1" pin="8"/>
<wire x1="20.32" y1="48.26" x2="53.34" y2="48.26" width="0.1524" layer="91"/>
<wire x1="53.34" y1="48.26" x2="53.34" y2="17.78" width="0.1524" layer="91"/>
<wire x1="53.34" y1="17.78" x2="66.04" y2="17.78" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="10-PIO1-SCK"/>
<wire x1="66.04" y1="17.78" x2="66.04" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="SV1" gate="1" pin="5"/>
<wire x1="20.32" y1="40.64" x2="50.8" y2="40.64" width="0.1524" layer="91"/>
<wire x1="50.8" y1="40.64" x2="50.8" y2="7.62" width="0.1524" layer="91"/>
<wire x1="50.8" y1="7.62" x2="78.74" y2="7.62" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="15-WAKEHW"/>
<wire x1="78.74" y1="7.62" x2="78.74" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="SV1" gate="1" pin="4"/>
<wire x1="20.32" y1="38.1" x2="48.26" y2="38.1" width="0.1524" layer="91"/>
<wire x1="48.26" y1="38.1" x2="48.26" y2="5.08" width="0.1524" layer="91"/>
<wire x1="48.26" y1="5.08" x2="71.12" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="12-WS-PIO3-MOSI"/>
<wire x1="71.12" y1="20.32" x2="71.12" y2="5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="SV1" gate="1" pin="7"/>
<wire x1="20.32" y1="45.72" x2="45.72" y2="45.72" width="0.1524" layer="91"/>
<wire x1="45.72" y1="45.72" x2="45.72" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="7-WAKESW"/>
<wire x1="45.72" y1="55.88" x2="50.8" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="SV1" gate="1" pin="6"/>
<wire x1="20.32" y1="43.18" x2="45.72" y2="43.18" width="0.1524" layer="91"/>
<wire x1="45.72" y1="43.18" x2="45.72" y2="15.24" width="0.1524" layer="91"/>
<wire x1="45.72" y1="15.24" x2="68.58" y2="15.24" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="11-MLDPEV-PIO2-CS"/>
<wire x1="68.58" y1="15.24" x2="68.58" y2="20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<wire x1="33.02" y1="7.62" x2="43.18" y2="7.62" width="0.1524" layer="91"/>
<wire x1="43.18" y1="7.62" x2="43.18" y2="63.5" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="4-AIO0"/>
<wire x1="43.18" y1="63.5" x2="50.8" y2="63.5" width="0.1524" layer="91"/>
<pinref part="SV3" gate="1" pin="6"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<wire x1="33.02" y1="10.16" x2="40.64" y2="10.16" width="0.1524" layer="91"/>
<wire x1="40.64" y1="10.16" x2="40.64" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="3-AIO1"/>
<wire x1="40.64" y1="66.04" x2="50.8" y2="66.04" width="0.1524" layer="91"/>
<pinref part="SV3" gate="1" pin="7"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<wire x1="33.02" y1="12.7" x2="38.1" y2="12.7" width="0.1524" layer="91"/>
<wire x1="38.1" y1="12.7" x2="38.1" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="2-AIO2"/>
<wire x1="38.1" y1="68.58" x2="50.8" y2="68.58" width="0.1524" layer="91"/>
<pinref part="SV3" gate="1" pin="8"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<wire x1="33.02" y1="5.08" x2="45.72" y2="5.08" width="0.1524" layer="91"/>
<wire x1="45.72" y1="5.08" x2="45.72" y2="2.54" width="0.1524" layer="91"/>
<wire x1="45.72" y1="2.54" x2="73.66" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="13-PIO4-MISO"/>
<wire x1="73.66" y1="2.54" x2="73.66" y2="20.32" width="0.1524" layer="91"/>
<pinref part="SV3" gate="1" pin="5"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<wire x1="33.02" y1="2.54" x2="43.18" y2="2.54" width="0.1524" layer="91"/>
<wire x1="43.18" y1="2.54" x2="43.18" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="43.18" y1="-2.54" x2="99.06" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="99.06" y1="-2.54" x2="99.06" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="17-SPI-/PIO"/>
<wire x1="99.06" y1="53.34" x2="93.98" y2="53.34" width="0.1524" layer="91"/>
<pinref part="SV3" gate="1" pin="4"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<wire x1="33.02" y1="0" x2="40.64" y2="0" width="0.1524" layer="91"/>
<wire x1="40.64" y1="0" x2="40.64" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="40.64" y1="-5.08" x2="104.14" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-5.08" x2="104.14" y2="58.42" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="19-PIO7"/>
<wire x1="104.14" y1="58.42" x2="93.98" y2="58.42" width="0.1524" layer="91"/>
<pinref part="SV3" gate="1" pin="3"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>

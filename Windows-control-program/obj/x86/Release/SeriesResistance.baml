   M S B A M L   `   `   `  ���� E  AMightyWatt, Version=3.1.4.0, Culture=neutral, PublicKeyToken=null'clr-namespace:MightyWatt
MightyWatt  !    MightyWatt.SeriesResistance   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     *localclr-namespace:MightyWatt       � Title$  Series resistance�� � WindowStyle$ 
ToolWindow=� � 
ResizeMode$ NoResize=�$	��300��$	��300��.��� .+��� -   $��textBoxResistance��$��23��$
��Left=�$��8,8,0,0q�$	��Top=�$��60��$��1�� �� 	MaxLength$ 6���� -   $��buttonOK��$��OK��$��23��$
��Left=�$��	110,8,0,0q�$	��Top=�$��60�� �� 	IsDefault .  J� RenderTransformOrigin$ 2,-0.652&��� -   $��buttonCancel��$��Cancel��$��23��$
��Left=�$��	176,8,0,0q�$	��Top=�$��60�� �� IsCancel . �� -    ��Name$ 	textBlock��$��
6,66,10,10q�$
��Wrap=�$
��Auto=��� $��14(�$��Segoe UI)�$	�▪���� $� ���� $���This feature allows specifing a resistance that is connected in series with MightyWatt. It can be cable resistance or deliberately added power resistor. The value is only used to recalculate the allowable power dissipation in remote mode. No visible or logged values are affected. Use this feature with caution.���� �� �� �� $��14(�$��Segoe UI)�$	�▪���� $� ���� $d�^For enhanced safety, load can be automatically stopped when a selected power threshold of the ���� $�series resistance ���� $�is exceeded.���� -    ��Name$ labelUnitOhm��$��Ω��$
��Left=�$��69,4,0,0q�$	��Top=��� -   	 ��Name$	 textBoxPower��$��23��$
��Left=�$��8,38,0,0q�$	��Top=�$��60��$	��100��$ 6���� -   $ 
labelUnitW��$��W��$
��Left=�$��	69,34,0,0q�$	��Top=��� -   
 ��Name$
 checkBoxPower��$��Stop load when exceeded��$
��Left=�$��
110,40,0,0q�$	��Top=�$��21��$	��174��
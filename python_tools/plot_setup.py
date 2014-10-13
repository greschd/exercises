#!/usr/bin/python3
# -*- coding: utf-8 -*-
#
# Author:  Dominik Gresch <greschd@ethz.ch>
# Date:    06.10.2014 17:39:24 CEST
# File:    plot_setup.py

import matplotlib.pyplot as plt
from matplotlib.pyplot import rc
from matplotlib.font_manager import FontProperties
rc('text', usetex=True)
background_color = '#eeeeee' 
grid_color = 'white' #FAFAF7'
rc('axes', facecolor = background_color)
rc('axes', edgecolor = grid_color)
rc('axes', linewidth = 1.2)
rc('axes', grid = True )
rc('axes', axisbelow = True)
rc('grid',color = grid_color)
rc('grid',linestyle='-' )
rc('grid',linewidth=0.7 )
rc('xtick.major',size =0 )
rc('xtick.minor',size =0 )
rc('ytick.major',size =0 )
rc('ytick.minor',size =0 )
rc('font',**{'family':'sans-serif', 'sans-serif':['Gill Sans MT']})
rc('text.latex', preamble=r'\usepackage{cmbright}')
rc('mathtext', fontset='stixsans')

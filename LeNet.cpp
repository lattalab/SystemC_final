#include "LeNet.h"

void Conv_pool::run2()
{
  if(rst) //all reset to zero
  {
  rom_rd=0;
  rom_addr=0;
  dense_en=0;
  state=0;
  }
  else  //we want to store the data from ROM
  {
    if(!dense_en)
    {
    if(state<=157) //read conv1 weight(0~155)
    {
    rom_rd.write(1);
    rom_addr=state;
  
    //By doing this,we can make conv1[0]=first number....(cause when state=0,1¡Athe data isn't the data we want)
    if(state>=2)
    {conv1[state-2]=rom_data_out.read();}
    state++;
    
    }
    else if(state>=158&&state<=2573) //read conv2 weight(156~2571)
    {
    rom_rd.write(1);
    rom_addr=state;
  
    //By doing this,we can make conv2[0]=156th number....
    if(state>=158)
    {conv2[state-158]=rom_data_out.read();}
    state++;
    }
    else if(state>=2574&&state<=33413) //read dense1 weight(2572~33411) 
    {
    rom_rd.write(1);
    rom_addr=state;

  
    //By doing this,we can make dense1[0]=2574th number....
    if(state>=2574)
    {dense1[state-2574]=rom_data_out.read();}
    state++;
    }
    else if(state>=33414&&state<=43577) //read dense2 weight(33412~43575) 
    {
    rom_rd.write(1);
    rom_addr=state;
                                                                                
    //By doing this,we can make dense2[0]=33412th number....
    if(state>=33414)
    {dense2[state-33414]=rom_data_out.read();}
    state++;
    }
    else if(state>=43578&&state<=44427) //read dense3 weight(43576~44425) 
    {
    rom_rd.write(1);
    rom_addr=state;
  
    //By doing this,we can make dense3[0]=43578th number....
    if(state>=43578)
    {dense3[state-43578]=rom_data_out.read();}
    state++;
    } //end else if
    else if(state>=44428&&state<=45211) //read input data(44426~45209) 
    {
    rom_rd.write(1);
    rom_addr=state;
  
    //By doing this,we can make input[0]=44426th number....
    if(state>=44428)
    {input[state-44428]=rom_data_out.read();   }
    state++;
    } //end else if
    else if(state==45212) //do conv1
    {
                                   
    state++;
    int i=0;
      for(int w=0;w<6;w++) //which kernel
      {
          for(int k=0;k<24;k++) //move height
          {
            for(int j=0;j<24;j++) //move width
            {
              //do convolution operation
              output[i]+=conv1[0+26*w]*input[0+j+28*k]+conv1[1+26*w]*input[1+j+28*k]+conv1[2+26*w]*input[2+j+28*k]+conv1[3+26*w]*input[3+j+28*k]+conv1[4+26*w]*input[4+j+28*k];
              output[i]+=conv1[5+26*w]*input[28+j+28*k]+conv1[6+26*w]*input[29+j+28*k]+conv1[7+26*w]*input[30+j+28*k]+conv1[8+26*w]*input[31+j+28*k]+conv1[9+26*w]*input[32+j+28*k];
              output[i]+=conv1[10+26*w]*input[56+j+28*k]+conv1[11+26*w]*input[57+j+28*k]+conv1[12+26*w]*input[58+j+28*k]+conv1[13+26*w]*input[59+j+28*k]+conv1[14+26*w]*input[60+j+28*k];
              output[i]+=conv1[15+26*w]*input[84+j+28*k]+conv1[16+26*w]*input[85+j+28*k]+conv1[17+26*w]*input[86+j+28*k]+conv1[18+26*w]*input[87+j+28*k]+conv1[19+26*w]*input[88+j+28*k];
              output[i]+=conv1[20+26*w]*input[112+j+28*k]+conv1[21+26*w]*input[113+j+28*k]+conv1[22+26*w]*input[114+j+28*k]+conv1[23+26*w]*input[115+j+28*k]+conv1[24+26*w]*input[116+j+28*k];
              //plus bias
              output[i]+=conv1[25+26*w];
              //do ReLU function
              if(output[i]<0)
              output[i]=0;
                  i++;
              }    
          }
  
         
        }
                                                                                   
                                                                       
    } //end else if
    else if(state==45213) //do maxpool_1
    {
    state++;
    int i = 0;
        for(int w=0;w<6;w++) //which layer of input
        {
          for(int k=0;k<24;k+=2) //change height
          {  
            for(int j=0;j<24;j+=2) //change width
            {
              output2[i]=max(output[j+(24*k)+w*576],output[j+1+(24*k)+w*576],output[j+24+(24*k)+w*576],output[j+25+(24*k)+w*576]);
              i+=1;
            }
          }
         
        }
                                                                               

    }
    else if(state==45214) //do conv2
    {
    state++;
    int i=0,index=0,bias_con=150;
      for(int w=0;w<16;w++) //which kernel
      {
          for(int p=0;p<6;p++) //which picture
          {
          i=0;
          for(int k=0;k<8;k++) //move height
          {
            for(int j=0;j<8;j++) //move width
            {
              //do convolution operation
              temp[p][i]+=conv2[0+25*p]*output2[0+j+12*k+144*p]+conv2[1+25*p]*output2[1+j+12*k+144*p]+conv2[2+25*p]*output2[2+j+12*k+144*p]+conv2[3+25*p]*output2[3+j+12*k+144*p]+conv2[4+25*p]*output2[4+j+12*k+144*p];
              
              temp[p][i]+=conv2[5+25*p]*output2[12+j+12*k+144*p]+conv2[6+25*p]*output2[13+j+12*k+144*p]+conv2[7+25*p]*output2[14+j+12*k+144*p]+conv2[8+25*p]*output2[15+j+12*k+144*p]+conv2[9+25*p]*output2[16+j+12*k+144*p];
              
              temp[p][i]+=conv2[10+25*p]*output2[24+j+12*k+144*p]+conv2[11+25*p]*output2[25+j+12*k+144*p]+conv2[12+25*p]*output2[26+j+12*k+144*p]+conv2[13+25*p]*output2[27+j+12*k+144*p]+conv2[14+25*p]*output2[28+j+12*k+144*p];
              
              temp[p][i]+=conv2[15+25*p]*output2[36+j+12*k+144*p]+conv2[16+25*p]*output2[37+j+12*k+144*p]+conv2[17+25*p]*output2[38+j+12*k+144*p]+conv2[18+25*p]*output2[39+j+12*k+144*p]+conv2[19+25*p]*output2[40+j+12*k+144*p];
              temp[p][i]+=conv2[20+25*p]*output2[48+j+12*k+144*p]+conv2[21+25*p]*output2[49+j+12*k+144*p]+conv2[22+25*p]*output2[50+j+12*k+144*p]+conv2[23+25*p]*output2[51+j+12*k+144*p]+conv2[24+25*p]*output2[52+j+12*k+144*p];
              
              i++;
              }    
          }
          }

          for(int i=0;i<64;i++)
          {
         
        output3[i+64*w]=temp[0][i]+temp[1][i]+temp[2][i]+temp[3][i]+temp[4][i]+temp[5][i]+conv2[bias_con+w*151];
          
          //do ReLU function
            if(output3[i+64*w]<0)
            output3[i+64*w]=0;
         
          }
          
          for(int j=0;j<6;j++) //reset zero
          {
            for(int i=0;i<64;i++)
            temp[j][i]=0;
          }
         
        }
        
                                                                                                                       
    }//end else if
    else if(state==45215) //do maxpool_2
    {
    state++;
    int index=0;
    
    for(int i=0;i<16;i++) //which picture
    {
        for(int k=0;k<8;k+=2) //change height
        {
            for(int j=0;j<8;j+=2) //change width
            {
            output4[index]=max(output3[j+8*k+64*i],output3[j+1+(8*k)+64*i],output3[j+8+(8*k)+64*i],output3[j+9+(8*k)+64*i]);
            index++;
            }
        }
    }
                                                  
    
    }//end of else if
    else if(state==45216) //the data wanted to send to dense will be stored in a large array.
    {
    state++;
    int index=0;
                                            
    for(int i=0;i<30840;i++) //read dense1
    {
    total[index++]=dense1[i];
                          
                             
    }
                                     
    for(int i=0;i<10164;i++) //read dense2
    {
    total[index++]=dense2[i];
                              
    }
                                 
    for(int i=0;i<850;i++)   //read dense3
    {
    total[index++]=dense3[i];
                                        
    }
                                     
    for(int i=0;i<256;i++) //read the data that will be send to dense layer;
    {
    total[index++]=output4[i];
    }
    dense_en=1;
    
    }
    
    
    }//end dense_en if
    
    else //write data to dense layer
    {
    if(conv_pool_rd.read())
    conv_pool_data_out.write(total[conv_pool_addr.read()]);
    
    }
    
    
  } //end else
  
}//end of function
void Dense::run(){
    if(dense_en) 
    {
    conv_pool_addr=state;
    if(state< 30842) //read dense1 data
    {
    conv_pool_rd=1;
    conv_pool_addr=state;
    if(state>=2)
    {dense1[state-2]=conv_pool_data_out.read();}
    state++;
    
    }
    else if(state>=30842&&state<41006) //read dense2 data
    {
    
    conv_pool_rd=1;
    conv_pool_addr=state;
    if(state>=30842)
    {dense2[state-30842]=conv_pool_data_out.read();}
    
    state++;
    
    }
    else if(state >= 41006&&state<=41855) //read dense3 data
    {
    conv_pool_rd=1;
    conv_pool_addr=state;
    if(state>=41006)
    {dense3[state-41006]=conv_pool_data_out.read();}
    
    state++;
    
    }
    else if(state>=41856&&state<=42111) //read the data after doing conv1¡Bmaxpool1¡Bconv2¡Bmaxpool2 (16*4*4)
    {
    conv_pool_rd=1;
    conv_pool_addr=state;
    if(state>=41856)
    {input[state-41856]=conv_pool_data_out.read();}
    state++;
    
    }
    else if(state==42112) //do dense layer1
    {
    state++;

    int index=0;
    for(int j=0;j<120;j++) //nth Neuron weight
    {
        for(int i=0;i<256;i++) //input send into a Neuron
        {
            out1[index]+=input[i]*dense1[i+257*j];
        }
        out1[index]+=dense1[256+j*257]; //plus bias
        //do ReLU function
            if(out1[index]<0)
            out1[index]=0;
            index++;
            
    }
    
    }//end else if
    else if(state==42113) //do dense layer2
    {
    state++;
    int index2=0;
    for(int j=0;j<84;j++) //nth Neuron weight
    {
        for(int i=0;i<120;i++) //input send into a Neuron
        {
            out2[index2]+=out1[i]*dense2[i+121*j];
        }
        out2[index2++]+=dense2[120+j*121]; //plus bias
        //do ReLU function
            if(out2[index2]<0)
            out2[index2]=0;
            index2++;
            
    }
    
    }//end else if
    else if(state==42114) //do dense layer3
    {
    state++;
    int index3=0;
    for(int j=0;j<10;j++) //nth Neuron weight
    {
        for(int i=0;i<84;i++) //input send into a Neuron
        {
            out3[index3]+=out2[i]*dense3[i+85*j];
        }
        out3[index3++]+=dense3[84+j*85]; //plus bias
    }
    
    }//end else if
    else if(state<=42115+10) //send to monitor
    {
    
    output_valid=1;
    result.write(out3[state-42115]);
    state++;
    } //end eles if
    
    
    }//end big if
    
    
    
}
// ^^^^^ put your code here ^^^^^

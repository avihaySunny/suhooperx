import React from 'react'
import './custom-button-styles.scss'

const CustomButton = (props) =>(
    <button className='custom-button'> 
        {props.children}
       </button> 
)

export default CustomButton

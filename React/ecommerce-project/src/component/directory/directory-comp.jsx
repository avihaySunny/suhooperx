import React, { Component } from 'react'
import MenuItem from '../menu-item/menu-item-comp'
import {sections} from './directory.data'
import './directory-comp-styles.scss'

export class Directory extends Component {
    constructor(props){
        super(props)

        this.state = {
            sections
        }
    }

    render() {
        return (
            <div className='directory-menu'>
                {
                    this.state.sections.map(({id , ...otherSectionProps}) => (
                        <MenuItem key = {id} {...otherSectionProps}/>
                    ))
                }
            </div>
        )
    }
}

export default Directory

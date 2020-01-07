import React, { Component } from 'react'
import FormInput from '../../component/form-input/form-input-component'
export class SignIn extends Component {
    constructor(props){
        super(props)
        this.state={
            email:'', 
            password:''
        }
    }
    handleChange = event => {
        console.log(event.target.value)
        const {value, name} = event.target
        this.setState({[name]:value})
    }

    handleSubmit = event => {
        event.preventDefault()
        this.setState({email:'', password:''})
    }
    render() {
        return (
            <div className='sign-in'>
                <h2> Already have an account? </h2>
                <span>Sign in with your email and password </span>
                
            
            <form onSubmit={this.handleSubmit}>
                <FormInput name='email' type='email' handleChange={this.handleChange} value={this.state.email} label ='email' required/>
                <label>email</label>
                <FormInput 
                    name='password' 
                    type='password' 
                    value={this.state.password} 
                    label = 'password'
                    handleChange={this.handleChange}
                    required/>
                <label>Password</label>
                <input type = 'submit' value = 'Submit Form'/>
            </form>
            </div>
        )
    }
}

export default SignIn

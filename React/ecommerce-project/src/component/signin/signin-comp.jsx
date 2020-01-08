import React, { Component } from 'react'
import './signin-comp-styles.scss'
import FormInput from '../../component/form-input/form-input-component'
import CustomButton from '../../component/custom-button/custom-button-comp' 
import {auth, signInWithGoogle} from '../../firebase/firebase.util'
class SignIn extends Component {
    constructor(props){
        super(props)
        this.state={
            email:'', 
            password:''
        }
    }
    handleChange = event => {
        const {value, name} = event.target
        this.setState({[name]:value})
    }

    handleSubmit = async event => {
        event.preventDefault()
        const {email, password} = this.state
        try{
            await auth.signInWithEmailAndPassword(email,password);
            this.setState({email:'', password:''}, ()=>console.log('hello'))
        }catch(err){
            console.log(err)
        }
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
                <CustomButton type='submit'> Sign In</CustomButton>
                <CustomButton onClick={signInWithGoogle}> Sign In with google </CustomButton>
            </form>
            </div>
        )
    }
}

export default SignIn

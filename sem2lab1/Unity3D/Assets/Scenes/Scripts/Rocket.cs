using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
/// <summary>
/// The main <c>Math</c> class.
/// Contains all methods for performing basic math functions.
/// <list type="bullet">
/// <item>
/// <term>Add</term>
/// <description>Addition Operation</description>
/// </item>
/// <item>
/// <term>Subtract</term>
/// <description>Subtraction Operation</description>
/// </item>
/// <item>
/// <term>Multiply</term>
/// <description>Multiplication Operation</description>
/// </item>
/// <item>
/// <term>Divide</term>
/// <description>Division Operation</description>
/// </item>
/// </list>
/// </summary>
/// <remarks>
/// <para>This class can add, subtract, multiply and divide.</para>
/// <para>These operations can be performed on both integers and doubles.</para>
/// </remarks>
public class Rocket : MonoBehaviour
{
    //State
    enum State { Alive, Dying, Transcending }
    State state = State.Alive;
    //
    Rigidbody rigidBody;
    AudioSource audioSource;
    [SerializeField] float rcsThrust = 100f;
    [SerializeField] float mainThrust = 10f;
    [SerializeField] float levelLoadDelay = 2f;
    [SerializeField] AudioClip mainEngine;
    [SerializeField] AudioClip Death;
    [SerializeField] AudioClip GoToNextLevel;

    [SerializeField] ParticleSystem mainEngineParticles;
    [SerializeField] ParticleSystem DeathParticles;
    [SerializeField] ParticleSystem GoToNextLevelParticles;
    // Start is called before the first frame update
    void Start()
    {
        rigidBody = GetComponent<Rigidbody>();
        audioSource = GetComponent<AudioSource>();
        
    }

    // Update is called once per frame
    void Update()
    {
        if (state == State.Alive)
        {
            RespondToThrustInput();
            RespondToRotateInput();

        }
    }
    /// <summary>
    ///Determines the button for rotating the rocket and calculating the speed of rotation.
    /// </summary>
    /// <returns>
    /// Nothing
    /// </returns>
    /// See <see cref="Rocket.RespondToThrustInput()"/> to get to the acceleration of the rocket.
    /// <seealso cref="Rocket.ApplyThrust()"/>
    /// <seealso cref="Rocket.OnCollisionEnter(Collision)"/>
    /// <seealso cref="Rocket.StartNexLevelSequence()"/>
    /// <seealso cref="Rocket.StartDeathSequence()"/>
    private void RespondToRotateInput()
    {

        rigidBody.freezeRotation = true;
        
        float rotationThisFrame = Time.deltaTime * rcsThrust;
        if (Input.GetKey(KeyCode.A))
        {
            transform.Rotate(Vector3.forward * rotationThisFrame);
        }
        else if (Input.GetKey(KeyCode.D))
        {
            transform.Rotate(-Vector3.forward * rotationThisFrame);
        }
        rigidBody.freezeRotation = false;
    }
    /// <summary>
    /// Responsible for acceleration of the rocket. Determines the button("space") for thrusting
    /// </summary>
    /// <returns>
    /// Nothing
    /// </returns>
    /// See <see cref="Rocket.RespondToRotateInput"/> to get to the rotation of the rocket.
    private void RespondToThrustInput()
    {

        if (Input.GetKey(KeyCode.Space))
        {
            ApplyThrust();
        }
        else
        {
            audioSource.Stop();
            mainEngineParticles.Stop();
        }
    }
    /// <summary>
    /// Regulating accelerating force and thrusting sound.
    /// </summary>
    /// <returns>
    /// Nothing
    /// </returns>
    /// 
    private void ApplyThrust()
    {
        rigidBody.AddRelativeForce(Vector3.up * mainThrust);
        if (!audioSource.isPlaying)
        {
            audioSource.PlayOneShot(mainEngine);
        }
        mainEngineParticles.Play();
    }
    /// <summary>
    /// Tracks the incoming collision.
    /// </summary>
    /// <param name="collision">Parameter for collision</param>
    void OnCollisionEnter(Collision collision)
    {
        if (state != State.Alive) { return;}
        switch (collision.gameObject.tag)
        {
            case "Friendly": 
                break;
            case "Finish":
                StartNexLevelSequence();
                break;
            default:
                StartDeathSequence();
                break;
        }

    }

    /// <summary>
    /// Begins the loading of the next level.
    /// </summary>
    private void StartNexLevelSequence()
    {
        state = State.Transcending;
        GoToNextLevelParticles.Play();
        NextLevelSound();
        Invoke("LoadNextLevel", levelLoadDelay );
    }
    /// <summary>
    /// Disables to move. Creates an explosion.
    /// </summary>
    private void StartDeathSequence()
    {
        state = State.Dying;
        audioSource.Stop();
        DeathParticles.Play();
        DeathSound();
        Invoke("LoadFirstLevel", levelLoadDelay);
    }
    /// <summary>
    /// Creates the sound after hitting the landing pad.
    /// </summary>
    private void NextLevelSound()
    {
        audioSource.PlayOneShot(GoToNextLevel);

    }
    /// <summary>
    /// Creates the sound after hitting an obstacle
    /// </summary>
    private void DeathSound()
    {
        audioSource.PlayOneShot(Death);
    }
    /// <summary>
    /// Loads first level.
    /// </summary>
    private void LoadFirstLevel()
    {
        SceneManager.LoadScene(0);
    }
    /// <summary>
    /// Loads next level.
    /// </summary>
    private void LoadNextLevel()
    {
        SceneManager.LoadScene(1);
    }
}
